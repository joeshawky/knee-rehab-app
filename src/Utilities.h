#ifndef UTILITIES_H
#define UTILITIES_H

#include <QObject>

#define COLOR_RESET "\033[0m"

// ANSI escape codes for different colors
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

class Utilities : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString lightBgColor READ lightBgColor CONSTANT)
    Q_PROPERTY(QString darkBgColor READ darkBgColor CONSTANT)
    Q_PROPERTY(float widthCoefficient READ widthCoefficient CONSTANT)
    Q_PROPERTY(QString selectedDeviceName READ selectedDeviceName WRITE setSelectedDeviceName NOTIFY selectedDeviceNameChanged FINAL)
    Q_PROPERTY(QString defaultFont READ defaultFont CONSTANT)
    Q_PROPERTY(QString modeTextColor READ modeTextColor CONSTANT)

    Q_PROPERTY(QString currentQmlPage READ currentQmlPage WRITE setCurrentQmlPage NOTIFY currentQmlPageChanged FINAL)
public:
    explicit Utilities(QObject *parent = nullptr);



    QString darkBgColor() const;

    QString lightBgColor() const;


    QString selectedDeviceName() const;
    void setSelectedDeviceName(const QString &newSelectedDeviceName);

    float widthCoefficient() const;

    QString defaultFont() const;

    QString modeTextColor() const;

    QString currentQmlPage() const;
    void setCurrentQmlPage(const QString &newCurrentQmlPage);

public slots:
    void print(QString text);

signals:
    void selectedDeviceNameChanged();

    void currentQmlPageChanged();

private:
    QString m_lightBgColor;
    QString m_darkBgColor;

    QString m_selectedDeviceName;
    float m_widthCoefficient = 0.25;
    QString m_defaultFont;
    QString m_modeTextColor;
    QString m_currentQmlPage;
};

#endif // UTILITIES_H
