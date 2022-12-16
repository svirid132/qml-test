#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSql>
#include <controllers/deleteemployeecontroller.h>
#include <controllers/getadditionalempcontroller.h>
#include <controllers/postemployeecontroller.h>
#include <controllers/putemployeecontroller.h>
#include <datasqlite.h>
#include <models/countrymodel.h>
#include <puller/employeepuller.h>
#include <sqlitemanager.h>
#include <view/additionalemp.h>
#include "dataMeddiator.h"
#include "models/empmodel.h"
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

    qmlRegisterType<AdditionalEmp>("View", 1, 0, "AdditionalEmp");
    qmlRegisterType<Employee>("View", 1, 0, "Employee");
    qmlRegisterType<EmpModel>("Model", 1, 0, "EmpModel");
    qmlRegisterType<CountryModel>("Model", 1, 0, "CountryModel");
    qmlRegisterSingletonInstance<Employee>("Singelton", 1, 0, "Employee", new Employee);
    qmlRegisterType<getAdditionalEmpController>("Controllers", 1, 0, "GetAdditionalEmpController");
    qmlRegisterType<PutEmployeeController>("Controllers", 1, 0, "PutEmployeeController");
    qmlRegisterType<PostEmployeeController>("Controllers", 1, 0, "PostEmployeeController");
    qmlRegisterType<DeleteEmployeeController>("Controllers", 1, 0, "DeleteEmployeeController");
    qmlRegisterType<EmployeePuller>("Puller", 1, 0, "EmployeePuller");

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
