#ifndef BLUETOOTHSOCKETMANAGER_H
#define BLUETOOTHSOCKETMANAGER_H

#include <QObject>
#include <QBluetoothSocket>
#include <QTimer>

class BluetoothSocketManager : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothSocketManager(QObject *parent = nullptr);

    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged FINAL)
    Q_PROPERTY(float currentAngle READ currentAngle WRITE setCurrentAngle NOTIFY currentAngleChanged FINAL)
    Q_PROPERTY(float targetAngle READ targetAngle WRITE setTargetAngle NOTIFY targetAngleChanged FINAL)
    Q_PROPERTY(int targetAngleSeconds READ targetAngleSeconds WRITE setTargetAngleSeconds NOTIFY targetAngleSecondsChanged FINAL)
    Q_PROPERTY(QString currentMode READ currentMode WRITE setCurrentMode NOTIFY currentModeChanged FINAL)
    Q_PROPERTY(QString currentStatus READ currentStatus WRITE setCurrentStatus NOTIFY currentStatusChanged FINAL)

    Q_PROPERTY(float motorPowerVoltage READ motorPowerVoltage WRITE setMotorPowerVoltage NOTIFY motorPowerVoltageChanged FINAL)
    Q_PROPERTY(float motorPowerCurrent READ motorPowerCurrent WRITE setMotorPowerCurrent NOTIFY motorPowerCurrentChanged FINAL)
    Q_PROPERTY(float force READ force WRITE setForce NOTIFY forceChanged FINAL)
    Q_PROPERTY(bool rpConnected READ rpConnected WRITE setRpConnected NOTIFY rpConnectedChanged FINAL)

    float currentAngle() const;

    void setCurrentAngle(float newCurrentAngle);

    QString ip() const;
    void setIp(const QString &newIp);

    float targetAngle() const;
    void setTargetAngle(float newTargetAngle);

    QString currentMode() const;
    void setCurrentMode(const QString &newCurrentMode);

    QString currentStatus() const;
    void setCurrentStatus(const QString &newCurrentStatus);

    int targetAngleSeconds() const;
    void setTargetAngleSeconds(int newTargetAngleSeconds);

    float motorPowerVoltage() const;
    void setMotorPowerVoltage(float newMotorPowerVoltage);

    float motorPowerCurrent() const;
    void setMotorPowerCurrent(float newMotorPowerCurrent);

    void attemptConnect();
    bool rpConnected() const;
    void setRpConnected(bool newRpConnected);

    float force() const;
    void setForce(float newForce);

public slots:
    void setMode(QString mode);

    void toggleConnection();
signals:
    void currentAngleChanged();

    void ipChanged();

    void targetAngleChanged();

    void currentModeChanged();

    void currentStatusChanged();

    void targetAngleSecondsChanged();

    void motorPowerVoltageChanged();

    void motorPowerCurrentChanged();

    void rpConnectedChanged();

    void forceChanged();

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void errorOccurred(QBluetoothSocket::SocketError error);
private:
    QBluetoothSocket *m_socket;
    float m_currentAngle;
    QString m_ip;
    float m_targetAngle;
    QString m_currentMode;
    QString m_currentStatus;
    int m_targetAngleSeconds;
    float m_motorPowerVoltage;
    float m_motorPowerCurrent;
    bool m_rpConnected;
    QBluetoothAddress m_rpMacAddress;
    QBluetoothUuid m_rpUuid;

    float m_force;
};

#endif // BLUETOOTHSOCKETMANAGER_H
