#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    MainController controller(nullptr);
    controller.setEngine(&engine);
    engine.rootContext()->setContextProperty("controller", &controller);

    return app.exec();
}
