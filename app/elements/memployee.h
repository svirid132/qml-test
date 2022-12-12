#ifndef MEmployee_H
#define MEmployee_H

#include <QList>
#include <QString>
#include <QObject>
#include <QtQml/qqml.h>

/**
 * @brief The MEmployee class - Класс является посредниокм по передачи данных между meddiator и ui qml
 * В нем реализованны базовые свойства, которые нужны для UI
 * MEemloyee - mediator employee
 */
class MEmployee : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY changedFirstName)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY changedLastName)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY changedAddress)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY changedPhone)
    Q_PROPERTY(QString maritalStatus READ maritalStatus WRITE setMaritalStatus NOTIFY changedMaritalStatus)
    Q_PROPERTY(QList<int> countryCodes READ countryCodes WRITE setCountryCodes)

signals:
    void changedFirstName();
    void changedLastName();
    void changedAddress();
    void changedPhone();
    void changedMaritalStatus();

private:
    QString m_firstName = "sasha";
    QString m_lastName = "";
    QString m_address = "";
    QString m_phone;
    QString m_maritalStatus;
    QList<int> m_countryCodes;

public:
    MEmployee(QObject* parent = nullptr);
    ~MEmployee();

    QString firstName() const;
    QString lastName() const;
    QString address() const;
    QString phone() const;
    QString maritalStatus() const;
    QList<int> countryCodes();

    void setFirstName(const QString &s);
    void setLastName(const QString &s);
    void setAddress(const QString &s);
    void setPhone(const QString &s);
    void setMaritalStatus(const QString &s);
    void setCountryCodes(const QList<int>& countryCodes);
};

#endif // MEmployee_H
