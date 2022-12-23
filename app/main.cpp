#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSql>
#include <controller/employeecontroller.h>
#include <datasqlite.h>
#include <model/countrytable.h>
#include <model/employeetable.h>
#include <sqlitemanager.h>
#include <model/additionalemp.h>
#include <QApplication>
#include <QSqlError>
#include <datasqlite.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

    SQLite::SQLiteManager manager = SQLite::SQLiteManager::getInstance();
    QSqlError error = manager.initDB();

    if (error.isValid()) {
        qDebug() << error.text();
        return 1;
    }

    qmlRegisterType<AdditionalEmp>("Model", 1, 0, "AdditionalEmp");
    qmlRegisterType<Employee>("Model", 1, 0, "Employee");
    qmlRegisterType<EmployeeTable>("Model", 1, 0, "EmployeTable");
    qmlRegisterType<CountryTable>("Model", 1, 0, "CountryTable");
    qmlRegisterType<EmployeeController>("Controller", 1, 0, "EmployeeController");
    qmlRegisterSingletonType(QUrl("qrc:/SliceMainScreen.qml"), "Slice", 1, 0, "SliceMainScreen");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
