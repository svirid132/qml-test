#ifndef M_EMPLOYEE_H
#define M_EMPLOYEE_H

#include <QList>
#include <QString>
#include <QObject>
//#include <QtQml/qqml.h>

// Не работает с Qt 5.15.2 + cmake
// https://stackoverflow.com/questions/63509161/how-to-use-qml-element-with-cmake
// Пришлось отказаться от этой идеи и использовать QStringList
class M_Employee : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName)
    Q_PROPERTY(QString address READ address WRITE setAddress)
    Q_PROPERTY(QString phone READ phone WRITE setPhone)
    Q_PROPERTY(QString maritalStatus READ maritalStatus WRITE setMaritalStatus)
//    QML_ELEMENT

private:
    QString m_firstName;
    QString m_lastName;
    QString m_address;
    QString m_phone;
    QString m_maritalStatus;

public:
    M_Employee(QObject* parent = nullptr);
    ~M_Employee();

    QString firstName();
    QString lastName();
    QString address();
    QString phone();
    QString maritalStatus();

    void setFirstName(const QString &s);
    void setLastName(const QString &s);
    void setAddress(const QString &s);
    void setPhone(const QString &s);
    void setMaritalStatus(const QString &s);
};

//Q_DECLARE_METATYPE(M_Employee)

#endif // M_EMPLOYEE_H
