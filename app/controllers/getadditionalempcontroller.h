#ifndef GETADDITIONALEMPCONTROLLER_H
#define GETADDITIONALEMPCONTROLLER_H

#include <QObject>

#include <view/additionalemp.h>

class getAdditionalEmpController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int additionalId READ additionalId WRITE setAdditionalId NOTIFY additionalIdChanged)
    Q_PROPERTY(AdditionalEmp* additionalEmp READ additionalEmp WRITE setAdditionalEmp NOTIFY additionalEmpChanged)

public:
    explicit getAdditionalEmpController(QObject *parent = nullptr);

    int additionalId() { return m_additionalId; }
    AdditionalEmp* additionalEmp() {
        return m_additionalEmp;
    }
    void setAdditionalId(int id) {
        if (m_additionalId == id) {
            return;
        }
        m_additionalId = id;
        emit additionalIdChanged();
    }
    void setAdditionalEmp(AdditionalEmp* additionalEmp) {
        if (m_additionalEmp == additionalEmp) {
            return;
        }
        m_additionalEmp = additionalEmp;
        emit additionalEmpChanged();
    }

    Q_INVOKABLE void exec() {

    }

signals:
    void additionalIdChanged();
    void additionalEmpChanged();

private:
    int m_additionalId = -1;
    AdditionalEmp* m_additionalEmp;
};

#endif // GETADDITIONALEMPCONTROLLER_H
