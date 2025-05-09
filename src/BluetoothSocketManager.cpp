#include "BluetoothSocketManager.h"

BluetoothSocketManager::BluetoothSocketManager(QObject *parent)
    : QObject{parent}
    , m_socket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this))
    , m_targetAngle(-1.0)
    , m_currentAngle(-1.0)
    , m_ip("xx:xx:xx:xx")
    , m_motorPowerVoltage(24)
    , m_motorPowerCurrent(0)
    , m_force(0)
    , m_currentMode("IMPEDANCE CTRL STOP")
    // , m_rpMacAddress("B8:27:EB:AD:31:73")
    // , m_rpMacAddress("B8:27:EB:25:93:D1")
    , m_rpMacAddress("2C:CF:67:75:67:82")
    , m_rpUuid("{00001101-0000-1000-8000-00805f9b34fb}")
    , m_rpConnected(false)
{


    // m_socket->connectToService(m_rpMacAddress, m_rpUuid);
}


void BluetoothSocketManager::onConnected()
{
    setRpConnected(true);
}

void BluetoothSocketManager::onDisconnected()
{
    setRpConnected(false);
}

void BluetoothSocketManager::onReadyRead()
{
    // qDebug() << "Reading!";
    QByteArray data = m_socket->readAll();
    QString dataString(data);

    QStringList dataFields = dataString.split(":", Qt::SkipEmptyParts);

    for (const QString &field : dataFields) {
        if (field.startsWith("ip=")) {
            setIp(field.mid(QString("ip=").length()));
        } else if (field.startsWith("current_angle=")) {
            setCurrentAngle(field.mid(QString("current_angle=").length()).toFloat());
        } else if (field.startsWith("target_angle=")) {
            QStringList targetParts = field.mid(QString("target_angle=").length()).split(",");
            setTargetAngle(targetParts[0].toFloat());
            setTargetAngleSeconds(targetParts[1].remove("S").toInt());
        } else if (field.startsWith("motor_power=")) {
            QStringList motorParts = field.mid(QString("motor_power=").length()).split(",");
            setMotorPowerVoltage(motorParts[0].remove("V").toFloat());
            setMotorPowerCurrent(motorParts[1].remove("A").toFloat());
        } else if (field.startsWith("current_mode=")) {
            QStringList modeParts = field.mid(QString("current_mode=").length()).split(" ");
            setCurrentMode(modeParts[0]);
            setCurrentStatus(modeParts[1]);
        } else if (field.startsWith("force=")){
            setForce(field.mid(QString("force=").length()).toFloat());
        }
    }



    //"ip=192.168.1.100:
    //current_angle=3.25:
    //target_angle=-1.0,-1S:
    //battery_status=8.225V,0.025A:
    //motor_power=12.28V,1.625A:
    //current_mode=FREE_MODE MODE_STOP

    // "ip=172.18.227.18:"
    // "current_angle=28.0:"
    // "target_angle=0,0S:"
    // "battery_status=0V,0A:"
    // "motor_power=0V,0A:"
    // "current_mode=FREE_MODE MODE_STOP"

}

void BluetoothSocketManager::errorOccurred(QBluetoothSocket::SocketError error)
{
    qDebug() << "Error occured!: " << error;
}

float BluetoothSocketManager::currentAngle() const
{
    return m_currentAngle;
}

void BluetoothSocketManager::setCurrentAngle(float newCurrentAngle)
{
    if (qFuzzyCompare(m_currentAngle, newCurrentAngle))
        return;
    m_currentAngle = newCurrentAngle;
    emit currentAngleChanged();
}

QString BluetoothSocketManager::ip() const
{
    return m_ip;
}

void BluetoothSocketManager::setIp(const QString &newIp)
{
    if (m_ip == newIp)
        return;
    m_ip = newIp;
    emit ipChanged();
}

float BluetoothSocketManager::targetAngle() const
{
    return m_targetAngle;
}

void BluetoothSocketManager::setTargetAngle(float newTargetAngle)
{
    if (qFuzzyCompare(m_targetAngle, newTargetAngle))
        return;
    m_targetAngle = newTargetAngle;
    emit targetAngleChanged();
}


QString BluetoothSocketManager::currentMode() const
{
    return m_currentMode;
}

void BluetoothSocketManager::setCurrentMode(const QString &newCurrentMode)
{
    if (m_currentMode == newCurrentMode)
        return;
    m_currentMode = newCurrentMode;
    emit currentModeChanged();
}

QString BluetoothSocketManager::currentStatus() const
{
    return m_currentStatus;
}

void BluetoothSocketManager::setCurrentStatus(const QString &newCurrentStatus)
{
    if (m_currentStatus == newCurrentStatus)
        return;
    m_currentStatus = newCurrentStatus;
    emit currentStatusChanged();
}

void BluetoothSocketManager::setMode(QString mode)
{
    QString targetStatus = m_currentStatus == "MODE_STOP" ? "MODE_START" : "MODE_STOP";
    QString command = QString("set_mode=%1:%2").arg(mode).arg(targetStatus);
    qDebug() << "set mode: " << mode;
    m_socket->write(command.toUtf8());
}

void BluetoothSocketManager::toggleConnection()
{
    bool deviceConnected = m_socket->state() == QBluetoothSocket::SocketState::ConnectedState;
    // qDebug() << "state: " << m_socket->state();
    if (deviceConnected)
    {
        m_socket->disconnectFromService();
        return;
    }

    if (m_socket)
        m_socket->deleteLater();


    m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    connect(m_socket, &QBluetoothSocket::connected, this, &BluetoothSocketManager::onConnected);
    connect(m_socket, &QBluetoothSocket::disconnected, this, &BluetoothSocketManager::onDisconnected);
    connect(m_socket, &QBluetoothSocket::readyRead, this, &BluetoothSocketManager::onReadyRead);
    connect(m_socket, &QBluetoothSocket::errorOccurred, this, &BluetoothSocketManager::errorOccurred);

    m_socket->connectToService(m_rpMacAddress, m_rpUuid);
}

int BluetoothSocketManager::targetAngleSeconds() const
{
    return m_targetAngleSeconds;
}

void BluetoothSocketManager::setTargetAngleSeconds(int newTargetAngleSeconds)
{
    if (m_targetAngleSeconds == newTargetAngleSeconds)
        return;
    m_targetAngleSeconds = newTargetAngleSeconds;
    emit targetAngleSecondsChanged();
}

float BluetoothSocketManager::motorPowerVoltage() const
{
    return m_motorPowerVoltage;
}

void BluetoothSocketManager::setMotorPowerVoltage(float newMotorPowerVoltage)
{
    if (qFuzzyCompare(m_motorPowerVoltage, newMotorPowerVoltage))
        return;
    m_motorPowerVoltage = newMotorPowerVoltage;
    emit motorPowerVoltageChanged();
}

float BluetoothSocketManager::motorPowerCurrent() const
{
    return m_motorPowerCurrent;
}

void BluetoothSocketManager::setMotorPowerCurrent(float newMotorPowerCurrent)
{
    if (qFuzzyCompare(m_motorPowerCurrent, newMotorPowerCurrent))
        return;
    m_motorPowerCurrent = newMotorPowerCurrent;
    emit motorPowerCurrentChanged();
}


bool BluetoothSocketManager::rpConnected() const
{
    return m_rpConnected;
}

void BluetoothSocketManager::setRpConnected(bool newRpConnected)
{
    if (m_rpConnected == newRpConnected)
        return;
    m_rpConnected = newRpConnected;
    emit rpConnectedChanged();
}

float BluetoothSocketManager::force() const
{
    return m_force;
}

void BluetoothSocketManager::setForce(float newForce)
{
    if (qFuzzyCompare(m_force, newForce))
        return;
    m_force = newForce;
    emit forceChanged();
}
