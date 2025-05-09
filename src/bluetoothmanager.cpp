#include "BluetoothManager.h"

BluetoothManager::BluetoothManager(QObject *parent)
    : QObject{parent}
    , m_discoveryAgent(new QBluetoothDeviceDiscoveryAgent(this))
    , m_socket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol))
    // , m_deviceUUID("94f39d29-7d6d-437d-973b-fba39e49d4ee")
    , m_deviceUUID("00001101-0000-1000-8000-00805F9B34FB")
    , m_benchmarkSendToggle(false)
    , m_benchmarkReceiveToggle(false)
    , m_timer(new QTimer())
{
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
        this, &BluetoothManager::deviceDiscovered);

    // Handle successful or failed connection
    connect(m_socket, &QBluetoothSocket::connected, this, &BluetoothManager::deviceConnected);

    connect(m_socket, &QBluetoothSocket::disconnected, this, &BluetoothManager::deviceDisconnected);

    connect(m_socket, &QBluetoothSocket::errorOccurred, this, &BluetoothManager::errorOccurred);

    connect(this, &BluetoothManager::benchmarkReceiveToggleChanged, this, &BluetoothManager::benchmarkReceive);

    connect(this, &BluetoothManager::benchmarkSendToggleChanged, this, &BluetoothManager::benchmarkSend);
    // connect(m_socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error), this, [=](QBluetoothSocket::SocketError error) {
    //     m_utilities.print("Error connecting to: " + deviceName + " - " + socket->errorString());
    // });
}

QString BluetoothManager::getDeviceAddress(QString deviceName)
{
    if (m_devicesInfo.contains(deviceName))
        return m_devicesInfo[deviceName];

    return QString();
}

QString BluetoothManager::connectedDeviceName()
{
    return m_connectedDevice->deviceName;
}

void BluetoothManager::benchmarkSend()
{
    if (m_benchmarkSendToggle){

        connect(m_timer, &QTimer::timeout, this, [this](){
        const char *data = "t";
        if (m_socket->isOpen()) {
            qint64 bytesWritten = m_socket->write(data);
        }

        });

        m_timer->setInterval(1);
        m_timer->start();
    }else{
        m_timer->stop();
    }
}

void BluetoothManager::benchmarkReceive()
{
    if (m_benchmarkReceiveToggle){
        connect(m_timer, &QTimer::timeout, this, [this](){
            QByteArray data = m_socket->readAll();  // Read all available data
            m_utilities.print("Received data: " + QString::fromUtf8(data));
        });

        m_timer->setInterval(1);
        m_timer->start();
    }else{
        m_timer->stop();
    }
}


void BluetoothManager::checkPermission()
{
    QBluetoothPermission permission{};
    permission.setCommunicationModes(QBluetoothPermission::Access);

    switch (qApp->checkPermission(permission)) {
    case Qt::PermissionStatus::Undetermined:
        m_utilities.print("Undetermined");
        // qApp->requestPermission(permission, this, &BluetoothManager::startSearch);
        return;
    case Qt::PermissionStatus::Denied:
        m_utilities.print("Denied");
        return;
    case Qt::PermissionStatus::Granted:
        m_utilities.print("Granted");
        break; // proceed to search
    }
}

void BluetoothManager::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    QString text = QString("address: %1, name: %2").arg(device.address().toString()).arg(device.name());
    m_utilities.print(text);
    bool deviceSaved = m_devicesInfo.contains(device.address().toString());
    bool noName = device.name().isEmpty();
    if (deviceSaved || noName)
        return;

    m_devicesInfo[device.name()] = device.address().toString();
    emit devicesNamesChanged();
}

void BluetoothManager::discoverDevices()
{
    m_devicesInfo.clear();
    emit devicesNamesChanged();
    m_discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::ClassicMethod);
}

void BluetoothManager::connectToDevice(QString test)
{
    QString macAddress = m_devicesInfo[test];
    m_utilities.print("Connecting to device name: " + test + " ,Mac address: " + macAddress);

    // Connect to the Raspberry Pi on its MAC address and port 4
    QBluetoothAddress address(macAddress);

    // Use the Serial Port Profile (SPP) UUID for the connection
    // QBluetoothUuid uuid(QStringLiteral("{94f39d29-7d6d-437d-973b-fba39e49d4ee}"));
    QBluetoothUuid uuid(m_deviceUUID);
    // QBluetoothUuid uuid(QStringLiteral("{00001101-0000-1000-8000-00805F9B34FB}"));


    m_socket->connectToService(address, uuid, QIODevice::ReadWrite);

    // BluetoothDevice device = BluetoothDevice(test, macAddress);
    m_connectedDevice = new BluetoothDevice(test, macAddress);


    // emit deviceConnected();
}

void BluetoothManager::disconnect()
{
    m_utilities.print("Disconnect slot!");
    m_socket->disconnectFromService();
}

void BluetoothManager::deviceConnected()
{
    m_utilities.print("Successfully connected to: " + m_connectedDevice->deviceName);
    m_deviceConnected = true;
    emit deviceConnectionChanged(m_deviceConnected);
}

void BluetoothManager::deviceDisconnected()
{
    m_utilities.print("Disconnected from: " + m_connectedDevice->deviceName);
    m_deviceConnected = false;
    m_connectedDevice = nullptr;
    m_benchmarkReceiveToggle = false;
    m_benchmarkSendToggle = false;
    emit deviceConnectionChanged(m_deviceConnected);
}

void BluetoothManager::errorOccurred(QBluetoothSocket::SocketError error)
{
    QString errorMsg;

    switch (error) {
    case QBluetoothSocket::SocketError::NoSocketError:
        errorMsg = "No error occurred";
        break;
    case QBluetoothSocket::SocketError::UnknownSocketError:
        errorMsg = "Unknown error";
        break;
    case QBluetoothSocket::SocketError::HostNotFoundError:
        errorMsg = "Host not found";
        break;
    case QBluetoothSocket::SocketError::ServiceNotFoundError:
        errorMsg = "Service not found";
        break;
    case QBluetoothSocket::SocketError::NetworkError:
        errorMsg = "Network error";
        break;
    case QBluetoothSocket::SocketError::UnsupportedProtocolError:
        errorMsg = "Unsupported protocol error";
        break;
    default:
        errorMsg = QString("Unknown error occurred, code: %1").arg(static_cast<int>(error));
        break;
    }

    m_utilities.print("Error: " + errorMsg);
}

QList<QString> BluetoothManager::connectedDevices()
{
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;


    // Check if Bluetooth is available on this device
    if (localDevice.isValid()) {

        // Turn Bluetooth on
        localDevice.powerOn();

        // Read local device name
        localDeviceName = localDevice.name();

        // Make it visible to others
        // localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

        // Get connected devices
        QList<QBluetoothAddress> remotes;
        remotes = localDevice.connectedDevices();

        QList<QString>remotesStrings;

        foreach (QBluetoothAddress address, remotes) {
            m_utilities.print(QString("address: %1").arg(address.toString()));
            remotesStrings.append(address.toString());
        }

        return remotesStrings;
    }

    return QList<QString>();
}

QStringList BluetoothManager::testList()
{
    QList<QString> list;
    list.append("Hi");
    list.append("Bye");
    return QStringList(list);
}

void BluetoothManager::makeDiscoverable()
{
    QBluetoothPermission permission;
    permission.setCommunicationModes(QBluetoothPermission::Advertise);

    switch (qApp->checkPermission(permission)) {
    case Qt::PermissionStatus::Undetermined:
        m_utilities.print("Undetermined");
        qApp->requestPermission(permission, this, &BluetoothManager::makeDiscoverable);
        return;
    case Qt::PermissionStatus::Denied:
        m_utilities.print("Denied");
        return;
    case Qt::PermissionStatus::Granted:
        m_utilities.print("Granted");
        break; // proceed to search
    }


    QBluetoothLocalDevice localDevice;
    QString localDeviceName;

    // Check if Bluetooth is available on this device
    if (localDevice.isValid()) {

        // Turn Bluetooth on
        localDevice.powerOn();

        // Read local device name
        localDeviceName = localDevice.name();

        // Make it visible to others
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

        // Get connected devices
        QList<QBluetoothAddress> remotes;
        remotes = localDevice.connectedDevices();
    }



}


QStringList BluetoothManager::devicesNames() const
{
    return QStringList(m_devicesInfo.keys());
}



bool BluetoothManager::benchmarkSendToggle() const
{
    return m_benchmarkSendToggle;
}

void BluetoothManager::setBenchmarkSendToggle(bool newBenchmarkSendToggle)
{
    if (m_benchmarkSendToggle == newBenchmarkSendToggle)
        return;
    m_benchmarkSendToggle = newBenchmarkSendToggle;
    emit benchmarkSendToggleChanged();
}

bool BluetoothManager::benchmarkReceiveToggle() const
{
    return m_benchmarkReceiveToggle;
}

void BluetoothManager::setBenchmarkReceiveToggle(bool newBenchmarkReceiveToggle)
{
    if (m_benchmarkReceiveToggle == newBenchmarkReceiveToggle)
        return;
    m_benchmarkReceiveToggle = newBenchmarkReceiveToggle;
    emit benchmarkReceiveToggleChanged();
}
