#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSql>
#include <datasqlite.h>
#include <sqlitemanager.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    SQLiteManager manager;
    manager.isDriverExit();
    QSqlError error = manager.initDB();
    if (error.isValid()) {
        qDebug() << "initDb:" << error;
    }

    Employee emp;
    emp.firstName = "Александр";
    emp.lastName = "Свиридов";
    Additionally additionally;
    additionally.address = "Вязов";
    additionally.maritalStatus = "Не женат";
    additionally.phone = "123-123";
//    additionally.countries.append(Country{643, QString("Россия")});
//    additionally.countries.append(Country{895, QString("Абхазия")});
    QPair<Employee, Additionally> employee;
    QSqlError errorInsert = manager.execInsertEmployee(employee);
    qDebug() << "execInsertEmployee:" << errorInsert;
    manager.execDeleteEmployee(1, 2);

    return app.exec();
}
