#include <QtTest>
#include <QCoreApplication>
#include <QDebug>
#include <QPair>
#include <QSqlDatabase>
#include <QtSql/QSqlError>

#include "sqlitemanager.h"

//int *const ptr - константные указатели
//const int *ptr - константные значения

class SQLiteTest : public QObject
{
    Q_OBJECT

private:
    SQLiteManager manager = SQLiteManager::getInstance();
    Employee emp_1;
    Additionally add_1;
    Employee emp_2;
    Additionally add_2;

    bool isCompareEmployee(const QPair<Employee, Additionally>& before, const QPair<Employee, Additionally>& after);
    void checkSelect(const QList<QPair<Employee, Additionally>>& afterList);

private slots:
    void initTestCase();
    void insertEmps();
    void selectLastEmp();
    void selectEmps();
    void selectCountries();
    void updateEmps();
    void deleteEmps();
};

bool SQLiteTest::isCompareEmployee(const QPair<Employee, Additionally>& before, const QPair<Employee, Additionally>& after) {
//    qDebug() << before.first.id << after.first.id
//             << before.first.firstName << after.first.firstName
//             << before.first.lastName << after.first.lastName;
//    qDebug() << before.second.id << after.second.id
//             << before.second.address << before.second.address
//             << before.second.maritalStatus << after.second.maritalStatus
//             << before.second.phone << after.second.phone;
//    qDebug() << "before.first == after.first" << (before.first == after.first);
//    qDebug() << "before.second == after.second" << (before.second == after.second);
    return (before.first == after.first) && (before.second == after.second);
}

void SQLiteTest::checkSelect(const QList<QPair<Employee, Additionally>>& beforeList)
{
    QList<QPair<Employee, Additionally>> list = manager.execSelectEmployees();
    QVERIFY (beforeList.size() == list.size());

    for (int i = 0; i < beforeList.size(); ++i) {
        QVERIFY(isCompareEmployee(beforeList.at(i), list.at(i)));
    }
}

void SQLiteTest::initTestCase()
{
    QFile::remove("database");
    QSqlError error = manager.initDB();
    QVERIFY (!error.isValid());
}

void SQLiteTest::insertEmps()
{
    emp_1.firstName = "Влидамири";
    emp_1.lastName = "Клепиков";
    add_1.address = "Крыленко";
    add_1.codeCountries = {};
    add_1.maritalStatus = "Не женат";
    add_1.phone = "123 321";

    emp_2.firstName = "Владимек_1";
    emp_2.lastName = "Клепиков_1";
    add_2.address = "Крыленко";
    add_2.codeCountries = {895, 410, 498};
    add_2.maritalStatus = "женат";
    add_2.phone = "123 3";

    QSqlError error;
    error = manager.execInsertEmployee(QPair<Employee, Additionally>({emp_1, add_1}));
    QVERIFY (!error.isValid());
    error = manager.execInsertEmployee(QPair<Employee, Additionally>({emp_2, add_2}));
    QVERIFY (!error.isValid());
}

void SQLiteTest::selectLastEmp()
{
    emp_2.id = 2;
    emp_2.additionally_id = 2;
    add_2.id = 2;

    QPair<Employee, Additionally> emp = manager.execSelectLastEmp();
    QVERIFY (isCompareEmployee(emp, {emp_2, add_2}));
}

void SQLiteTest::selectEmps()
{
    emp_1.id = 1;
    emp_1.additionally_id = 1;
    add_1.id = 1;
    emp_2.id = 2;
    emp_2.additionally_id = 2;
    add_2.id = 2;

    checkSelect({{emp_1, add_1}, {emp_2, add_2}});
}

void SQLiteTest::selectCountries()
{
    QList<Country> list = manager.execSelectCountries();
    QVERIFY (list.size() == 7);
    QVERIFY (list.at(0).code == 895 && list.at(0).name == "Абхазия" &&
             list.at(1).code == 40 && list.at(1).name == "Австрия");
}

void SQLiteTest::updateEmps()
{
    emp_1.firstName = "Владимир";
    add_1.phone = "8 (965) 088-02-00";
    add_1.codeCountries = {410, 643, 804};

    emp_2.firstName = "Юра";
    emp_2.lastName = "Куликов";
    add_2.phone = "8 (965) 088-02-01";
    add_2.codeCountries = {};

    QSqlError error;
    error = manager.execUpdateEmployee(QPair<Employee, Additionally>({emp_1, add_1}));
    QVERIFY(!error.isValid());
    error = manager.execUpdateEmployee(QPair<Employee, Additionally>({emp_2, add_2}));
    QVERIFY(!error.isValid());
    checkSelect({{emp_1, add_1}, {emp_2, add_2}});
}

void SQLiteTest::deleteEmps()
{
    QSqlError error;
    error = manager.execDeleteEmployee(emp_1.id, add_1.id);
    QVERIFY(!error.isValid());
    checkSelect({{emp_2, add_2}});
    error = manager.execDeleteEmployee(add_2.id, add_2.id);
    QVERIFY(!error.isValid());
    checkSelect({});
}

QTEST_APPLESS_MAIN(SQLiteTest)
#include "sqlite-test.moc"
