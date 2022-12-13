#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSql>
#include <datasqlite.h>
#include <sqlitemanager.h>
#include <controllers/selectedusercontroller.h>
#include <view/additionalemp.h>
#include "meddiator.h"
#include "dataMeddiator.h"
#include "elements/memployee.h"
#include "models/empmodel.h"
#include <datasqlite.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    SQLite::SQLiteManager manager = SQLite::SQLiteManager::getInstance();
    QSqlError error = manager.initDB();

    if (error.isValid()) {
        qDebug() << error.text();
        return 1;
    }

    qmlRegisterType<MEmployee>("Elems", 1, 0, "MEmployee");
    qmlRegisterUncreatableType<MEmployee>("Elems", 1, 0, "Employee", "dont create Employee");
    qmlRegisterType<SelectedUserController>("Controllers", 1, 0, "SelectedUserController");
    qmlRegisterType<AdditionalEmp>("View", 1, 0, "AdditionalEmp");
    qmlRegisterType<EmpModel>("Model", 1, 0, "EmpModel");

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
