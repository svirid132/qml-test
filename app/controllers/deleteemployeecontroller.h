#ifndef DELETEEMPLOYEECONTROLLER_H
#define DELETEEMPLOYEECONTROLLER_H

#include "basecontroller.h"

#include <QObject>
#include <QSqlError>
#include <sqlitemanager.h>

class DeleteEmployeeController : public BaseController
{
    Q_OBJECT
    Q_PROPERTY(int empId READ empId WRITE setEmpId NOTIFY empIdChanged)
    Q_PROPERTY(int additionalId READ additionalId WRITE setAdditionalId NOTIFY additionalIdChanged)

public:
    explicit DeleteEmployeeController(BaseController *parent = nullptr);

    int empId() { return m_empId; }
    void setEmpId(int empId) {
        m_empId = empId;
        emit empIdChanged();
    }
    int additionalId() {return m_additionalId;}
    void setAdditionalId(int additionalId) {
        m_additionalId = additionalId;
        emit additionalIdChanged();
    }

    Q_INVOKABLE void del() {
        qDebug() << m_empId << m_additionalId;
        QSqlError error = manager.execDeleteEmployee(m_empId, m_additionalId);
        if (error.isValid()) {
            execOnError();
            return;
        }
        execOnAccess();
    }

signals:
    void empIdChanged();
    void additionalIdChanged();

private:
    int m_empId = -1;
    int m_additionalId = -1;
    SQLite::SQLiteManager manager = SQLite::SQLiteManager::getInstance();
};

#endif // DELETEEMPLOYEECONTROLLER_H
