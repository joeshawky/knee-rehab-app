#ifndef INTERNETSOCKETMANAGER_H
#define INTERNETSOCKETMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class InternetSocketManager : public QObject
{
    Q_OBJECT
public:
    explicit InternetSocketManager(QObject *parent = nullptr);

    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged FINAL)
    Q_PROPERTY(float currentAngle READ currentAngle WRITE setCurrentAngle NOTIFY currentAngleChanged FINAL)
    Q_PROPERTY(float targetAngle READ targetAngle WRITE setTargetAngle NOTIFY targetAngleChanged FINAL)
    Q_PROPERTY(int targetAngleSeconds READ targetAngleSeconds WRITE setTargetAngleSeconds NOTIFY targetAngleSecondsChanged FINAL)
    Q_PROPERTY(QString currentMode READ currentMode WRITE setCurrentMode NOTIFY currentModeChanged FINAL)
    Q_PROPERTY(QString currentStatus READ currentStatus WRITE setCurrentStatus NOTIFY currentStatusChanged FINAL)

    Q_PROPERTY(float batteryStatusVoltage READ batteryStatusVoltage WRITE setBatteryStatusVoltage NOTIFY batteryStatusVoltageChanged FINAL)
    Q_PROPERTY(float batteryStatusCurrent READ batteryStatusCurrent WRITE setBatteryStatusCurrent NOTIFY batteryStatusCurrentChanged FINAL)
    Q_PROPERTY(float motorPowerVoltage READ motorPowerVoltage WRITE setMotorPowerVoltage NOTIFY motorPowerVoltageChanged FINAL)
    Q_PROPERTY(float motorPowerCurrent READ motorPowerCurrent WRITE setMotorPowerCurrent NOTIFY motorPowerCurrentChanged FINAL)


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

    float batteryStatusVoltage() const;
    void setBatteryStatusVoltage(float newBatteryStatusVoltage);

    float batteryStatusCurrent() const;
    void setBatteryStatusCurrent(float newBatteryStatusCurrent);

    float motorPowerVoltage() const;
    void setMotorPowerVoltage(float newMotorPowerVoltage);

    float motorPowerCurrent() const;
    void setMotorPowerCurrent(float newMotorPowerCurrent);

    void attemptConnect();
public slots:
    void setMode(QString mode);

signals:
    void currentAngleChanged();

    void ipChanged();

    void targetAngleChanged();

    void currentModeChanged();

    void currentStatusChanged();

    void targetAngleSecondsChanged();

    void batteryStatusVoltageChanged();

    void batteryStatusCurrentChanged();

    void motorPowerVoltageChanged();

    void motorPowerCurrentChanged();

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpSocket *m_socket;
    float m_currentAngle;
    QString m_ip;
    float m_targetAngle;
    QString m_currentMode;
    QString m_currentStatus;
    int m_targetAngleSeconds;
    float m_batteryStatusVoltage;
    float m_batteryStatusCurrent;
    float m_motorPowerVoltage;
    float m_motorPowerCurrent;
    QTimer *m_reconnectTimer;
};

#endif // INTERNETSOCKETMANAGER_H
