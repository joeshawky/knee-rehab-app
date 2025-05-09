#include "Utilities.h"
#include <QDebug>

Utilities::Utilities(QObject *parent)
    : QObject{parent}
    , m_lightBgColor("#1A1D26")
    , m_darkBgColor("#01040D")
    , m_defaultFont("Roboto Mono")
    , m_modeTextColor("#D9D9D9")
    , m_currentQmlPage("qrc:/KneeRehab/ui/qml/HomePage.qml")
{}

void Utilities::print(QString text)
{
    qDebug() << COLOR_YELLOW << text << COLOR_RESET;
}

QString Utilities::lightBgColor() const
{
    return m_lightBgColor;
}

QString Utilities::darkBgColor() const
{
    return m_darkBgColor;
}

QString Utilities::selectedDeviceName() const
{
    return m_selectedDeviceName;
}

void Utilities::setSelectedDeviceName(const QString &newSelectedDeviceName)
{
    if (m_selectedDeviceName == newSelectedDeviceName)
        return;
    m_selectedDeviceName = newSelectedDeviceName;
    emit selectedDeviceNameChanged();
}

float Utilities::widthCoefficient() const
{
    return m_widthCoefficient;
}

QString Utilities::defaultFont() const
{
    return m_defaultFont;
}

QString Utilities::modeTextColor() const
{
    return m_modeTextColor;
}

QString Utilities::currentQmlPage() const
{
    return m_currentQmlPage;
}

void Utilities::setCurrentQmlPage(const QString &newCurrentQmlPage)
{
    if (m_currentQmlPage == newCurrentQmlPage)
        return;
    m_currentQmlPage = newCurrentQmlPage;
    emit currentQmlPageChanged();
}
