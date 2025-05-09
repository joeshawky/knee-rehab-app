#ifndef BLUETOOTHDEVICE_H
#define BLUETOOTHDEVICE_H

#include <QObject>

class BluetoothDevice : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothDevice(QObject *parent = nullptr);
    BluetoothDevice(QString deviceName, QString deviceMacAddress);

    QString deviceName;
    QString deviceMacAddress;

signals:
};

#endif // BLUETOOTHDEVICE_H
