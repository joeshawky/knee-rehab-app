#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QObject>
#include <QtBluetooth>
#include "Utilities.h"
#include "BluetoothDevice.h"

class BluetoothManager : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothManager(QObject *parent = nullptr);

    Q_PROPERTY(QStringList devicesNames READ devicesNames NOTIFY devicesNamesChanged FINAL)
    Q_INVOKABLE QString getDeviceAddress(QString deviceName);
    Q_INVOKABLE QString connectedDeviceName();


    Q_PROPERTY(bool benchmarkSendToggle READ benchmarkSendToggle WRITE setBenchmarkSendToggle NOTIFY benchmarkSendToggleChanged FINAL)
    Q_PROPERTY(bool benchmarkReceiveToggle READ benchmarkReceiveToggle WRITE setBenchmarkReceiveToggle NOTIFY benchmarkReceiveToggleChanged FINAL)



    QStringList devicesNames() const;
    void setdevicesNames(const QStringList &newDevicesNames);

    bool benchmarkSendToggle() const;
    void setBenchmarkSendToggle(bool newBenchmarkSendToggle);

    bool benchmarkReceiveToggle() const;
    void setBenchmarkReceiveToggle(bool newBenchmarkReceiveToggle);

public slots:
    void makeDiscoverable();
    void checkPermission();
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void discoverDevices();
    void connectToDevice(QString test);
    void disconnect();
    void deviceConnected();
    void deviceDisconnected();
    void errorOccurred(QBluetoothSocket::SocketError error);

    void benchmarkSend();
    void benchmarkReceive();

    QList<QString> connectedDevices();
    QStringList testList();

signals:
    void devicesNamesChanged();
    void deviceConnectionChanged(bool connectionStatus);

    void benchmarkSendToggleChanged();

    void benchmarkReceiveToggleChanged();

private:
    QBluetoothLocalDevice m_localDevice;
    QBluetoothDeviceDiscoveryAgent *m_discoveryAgent;
    Utilities m_utilities;
    QBluetoothSocket *m_socket;
    QMap<QString, QString> m_devicesInfo;
    QStringList m_devicesNames;

    QString m_deviceUUID;
    bool m_deviceConnected;
    BluetoothDevice *m_connectedDevice;
    bool m_benchmarkSendToggle;
    bool m_benchmarkReceiveToggle;

    QTimer *m_timer;
};

#endif // BLUETOOTHMANAGER_H
