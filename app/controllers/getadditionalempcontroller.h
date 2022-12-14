#ifndef GETADDITIONALEMPCONTROLLER_H
#define GETADDITIONALEMPCONTROLLER_H

#include <QList>
#include <QObject>
#include <sqlitemanager.h>

#include <view/additionalemp.h>

//Заполняет AdditionalEmp по additionalId
class getAdditionalEmpController : public QObject
{
    Q_OBJECT
    //Параметры
    Q_PROPERTY(int additionalId READ additionalId WRITE setAdditionalId NOTIFY additionalIdChanged)
    //Заполнянет (возвращает)
    Q_PROPERTY(AdditionalEmp* target READ target WRITE setTarget NOTIFY targetChanged)

public:
    explicit getAdditionalEmpController(QObject *parent = nullptr);

    int additionalId() { return m_additionalId; }
    AdditionalEmp* target() {
        return m_target;
    }
    void setAdditionalId(int id) {
        if (m_additionalId == id) {
            return;
        }
        m_additionalId = id;
        emit additionalIdChanged();
    }
    void setTarget(AdditionalEmp* additionalEmp) {
        if (m_target == additionalEmp) {
            return;
        }
        m_target = additionalEmp;
        emit targetChanged();
    }

    Q_INVOKABLE void exec() {
        QList<QPair<SQLite::Employee, SQLite::Additionally>> emps = sqliteManager.execSelectEmployees();
        for (const QPair<SQLite::Employee, SQLite::Additionally>& emp : qAsConst(emps)) {
            if (m_additionalId == emp.second.id) {
                m_target->setId(emp.second.id);
                m_target->setAddress(emp.second.address);
                m_target->setPhone(emp.second.phone);
                m_target->setMaritalStatus(emp.second.maritalStatus);
                m_target->setCountryCodes(emp.second.codeCountries);
            }
        }
    }

signals:
    void additionalIdChanged();
    void targetChanged();

private:
    int m_additionalId = -1;
    AdditionalEmp* m_target;
    SQLite::SQLiteManager sqliteManager = SQLite::SQLiteManager::getInstance();
};

#endif // GETADDITIONALEMPCONTROLLER_H
