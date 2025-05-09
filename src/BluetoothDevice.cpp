#include "BluetoothDevice.h"

BluetoothDevice::BluetoothDevice(QObject *parent)
    : QObject{parent}
{}

BluetoothDevice::BluetoothDevice(QString name, QString macAddress)
    : deviceName(name)
    , deviceMacAddress(macAddress)
{

}
