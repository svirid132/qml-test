#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSql>
#include <controllers/getadditionalempcontroller.h>
#include <datasqlite.h>
#include <models/countrymodel.h>
#include <puller/employeepuller.h>
#include <sqlitemanager.h>
#include <view/additionalemp.h>
#include "dataMeddiator.h"
#include "models/empmodel.h"
#include <QSqlError>
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

    qmlRegisterType<AdditionalEmp>("View", 1, 0, "AdditionalEmp");
    qmlRegisterType<Employee>("View", 1, 0, "Employee");
    qmlRegisterType<EmpModel>("Model", 1, 0, "EmpModel");
    qmlRegisterType<CountryModel>("Model", 1, 0, "CountryModel");
    qmlRegisterSingletonInstance<EmpModel>("SingeltonModel", 1, 0, "EditEmpModel", new EmpModel);
    qmlRegisterType<getAdditionalEmpController>("Controllers", 1, 0, "GetAdditionalEmpController");
    qmlRegisterType<EmployeePuller>("Puller", 1, 0, "EmployeePuller");

//    SQLite::Employee emp_1;
//    SQLite::Additionally add_1;
//    SQLite::Employee emp_2;
//    SQLite::Additionally add_2;

//    emp_1.firstName = "Влидамири";
//    emp_1.lastName = "Клепиков";
//    add_1.address = "Крыленко";
//    add_1.codeCountries = {};
//    add_1.maritalStatus = "Не женат";
//    add_1.phone = "123 321";

//    emp_2.firstName = "Владимек_1";
//    emp_2.lastName = "Клепиков_1";
//    add_2.address = "Крыленко";
//    add_2.codeCountries = {895, 410, 498};
//    add_2.maritalStatus = "женат";
//    add_2.phone = "123 3";

//    error = manager.execInsertEmployee(QPair<SQLite::Employee, SQLite::Additionally>({emp_1, add_1}));
//    qDebug() << error.isValid();
//    error = manager.execInsertEmployee(QPair<SQLite::Employee, SQLite::Additionally>({emp_2, add_2}));
//    qDebug() << error.isValid();

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
