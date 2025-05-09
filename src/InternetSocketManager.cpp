#include "InternetSocketManager.h"


InternetSocketManager::InternetSocketManager(QObject *parent)
    : QObject{parent}
    , m_socket(new QTcpSocket(this))
    , m_targetAngle(-1.0)
    , m_reconnectTimer(new QTimer(this))
{
    connect(m_socket, &QTcpSocket::connected, this, &InternetSocketManager::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &InternetSocketManager::onDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &InternetSocketManager::onReadyRead);

    // m_socket->connectToHost("172.18.227.18", 55556);
    m_reconnectTimer->setInterval(5000);
    connect(m_reconnectTimer, &QTimer::timeout, this, &InternetSocketManager::attemptConnect);

    m_reconnectTimer->start();
}

void InternetSocketManager::attemptConnect() {
    if (m_socket->state() == QTcpSocket::UnconnectedState) {
        qDebug() << "Connecting to host...";
        m_socket->connectToHost("172.18.227.18", 55556);
    }
}

void InternetSocketManager::onConnected()
{
    qDebug() << "Device connected!";
}

void InternetSocketManager::onDisconnected()
{
    qDebug() << "Device disconnected!";
}

void InternetSocketManager::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    QString dataString = QString(data);


    QStringList dataSplit = dataString.split(":");


    QString currentIp = dataSplit[0].remove("ip=");
    float currentAngle = dataSplit[1].remove("current_angle=").toFloat();

    QStringList targetAngleData = dataSplit[2].remove("target_angle=").split(",");
    float targetAngle = targetAngleData[0].toFloat();
    int targetAngleSeconds = targetAngleData[1].remove("S").toInt();

    QStringList batteryData = dataSplit[3].remove("battery_status=").split(",");
    float batteryVoltage = batteryData[0].remove("V").toFloat();
    float batteryCurrent = batteryData[1].remove("A").toFloat();

    QStringList motorPowerData = dataSplit[4].remove("motor_power=").split(",");
    float motorVoltage = motorPowerData[0].remove("V").toFloat();
    float motorCurrent = motorPowerData[1].remove("A").toFloat();

    QStringList current_mode_with_status = dataSplit[5].remove("current_mode=").split(" ");
    QString current_mode = current_mode_with_status[0];
    QString current_status = current_mode_with_status[1];


    // "ip=172.18.227.18:"
    // "current_angle=28.0:"
    // "target_angle=0:"
    // "battery_status=0V,0A:"
    // "motor_power=0V,0A:"
    // "current_mode=FREE_MODE MODE_STOP"

    // qDebug() << dataString;
    // qDebug() << "ip:" << currentIp;

    setIp(currentIp);
    setCurrentAngle(currentAngle);
    setTargetAngle(targetAngle);
    setTargetAngleSeconds(targetAngleSeconds);

    setBatteryStatusVoltage(batteryVoltage);
    setBatteryStatusCurrent(batteryCurrent);

    setMotorPowerVoltage(motorVoltage);
    setMotorPowerCurrent(motorCurrent);

    setCurrentMode(current_mode);
    setCurrentStatus(current_status);
}

float InternetSocketManager::currentAngle() const
{
    return m_currentAngle;
}

void InternetSocketManager::setCurrentAngle(float newCurrentAngle)
{
    if (qFuzzyCompare(m_currentAngle, newCurrentAngle))
        return;
    m_currentAngle = newCurrentAngle;
    emit currentAngleChanged();
}

QString InternetSocketManager::ip() const
{
    return m_ip;
}

void InternetSocketManager::setIp(const QString &newIp)
{
    if (m_ip == newIp)
        return;
    m_ip = newIp;
    emit ipChanged();
}

float InternetSocketManager::targetAngle() const
{
    return m_targetAngle;
}

void InternetSocketManager::setTargetAngle(float newTargetAngle)
{
    if (qFuzzyCompare(m_targetAngle, newTargetAngle))
        return;
    m_targetAngle = newTargetAngle;
    emit targetAngleChanged();
}


QString InternetSocketManager::currentMode() const
{
    return m_currentMode;
}

void InternetSocketManager::setCurrentMode(const QString &newCurrentMode)
{
    if (m_currentMode == newCurrentMode)
        return;
    m_currentMode = newCurrentMode;
    emit currentModeChanged();
}

QString InternetSocketManager::currentStatus() const
{
    return m_currentStatus;
}

void InternetSocketManager::setCurrentStatus(const QString &newCurrentStatus)
{
    if (m_currentStatus == newCurrentStatus)
        return;
    m_currentStatus = newCurrentStatus;
    emit currentStatusChanged();
}

void InternetSocketManager::setMode(QString mode)
{
    QString targetStatus = m_currentStatus == "MODE_STOP" ? "MODE_START" : "MODE_STOP";
    QString command = QString("set_mode=%1:%2").arg(mode).arg(targetStatus);

    m_socket->write(command.toUtf8());
}

int InternetSocketManager::targetAngleSeconds() const
{
    return m_targetAngleSeconds;
}

void InternetSocketManager::setTargetAngleSeconds(int newTargetAngleSeconds)
{
    if (m_targetAngleSeconds == newTargetAngleSeconds)
        return;
    m_targetAngleSeconds = newTargetAngleSeconds;
    emit targetAngleSecondsChanged();
}

float InternetSocketManager::batteryStatusVoltage() const
{
    return m_batteryStatusVoltage;
}

void InternetSocketManager::setBatteryStatusVoltage(float newBatteryStatusVoltage)
{
    if (qFuzzyCompare(m_batteryStatusVoltage, newBatteryStatusVoltage))
        return;
    m_batteryStatusVoltage = newBatteryStatusVoltage;
    emit batteryStatusVoltageChanged();
}

float InternetSocketManager::batteryStatusCurrent() const
{
    return m_batteryStatusCurrent;
}

void InternetSocketManager::setBatteryStatusCurrent(float newBatteryStatusCurrent)
{
    if (qFuzzyCompare(m_batteryStatusCurrent, newBatteryStatusCurrent))
        return;
    m_batteryStatusCurrent = newBatteryStatusCurrent;
    emit batteryStatusCurrentChanged();
}

float InternetSocketManager::motorPowerVoltage() const
{
    return m_motorPowerVoltage;
}

void InternetSocketManager::setMotorPowerVoltage(float newMotorPowerVoltage)
{
    if (qFuzzyCompare(m_motorPowerVoltage, newMotorPowerVoltage))
        return;
    m_motorPowerVoltage = newMotorPowerVoltage;
    emit motorPowerVoltageChanged();
}

float InternetSocketManager::motorPowerCurrent() const
{
    return m_motorPowerCurrent;
}

void InternetSocketManager::setMotorPowerCurrent(float newMotorPowerCurrent)
{
    if (qFuzzyCompare(m_motorPowerCurrent, newMotorPowerCurrent))
        return;
    m_motorPowerCurrent = newMotorPowerCurrent;
    emit motorPowerCurrentChanged();
}
