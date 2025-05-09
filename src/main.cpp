#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>



#include "BluetoothManager.h"
#include "BluetoothSocketManager.h"
#include "InternetSocketManager.h"
#include "Utilities.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    BluetoothManager bluetoothManager;

    QFontDatabase::addApplicationFont(":/fonts/robo-mono-bold-font");

    // bool exists = QFile::exists(":/images/purple-arrow.svg");
    // qDebug() << "exists: " << exists;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("bluetoothManager", &bluetoothManager);

    Utilities utilities;
    context->setContextProperty("utilities", &utilities);

    BluetoothSocketManager bluetoothSocketManager;
    context->setContextProperty("bluetoothSocketManager", &bluetoothSocketManager);

    const QUrl url(QStringLiteral("qrc:/KneeRehab/ui/qml/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);





    return app.exec();
}
