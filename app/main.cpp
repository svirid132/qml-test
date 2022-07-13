#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSql>
#include <datasqlite.h>
#include <sqlitemanager.h>
#include "meddiator.h"
#include "dataMeddiator.h"
#include "elements/memployee.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<MEmployee>("Elems", 1, 0, "MEmployee");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    Meddiator meddiator(engine);
    engine.load(url);

    return app.exec();
}
