#ifndef ADDITIONALEMP_H
#define ADDITIONALEMP_H

#include <QObject>

class AdditionalEmp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString maritalStatus READ maritalStatus WRITE setMaritalStatus NOTIFY maritalStatusChanged)
    Q_PROPERTY(QList<int> countryCodes READ countryCodes WRITE setCountryCodes NOTIFY countryCodesChanged)

public:
    explicit AdditionalEmp(QObject *parent = nullptr);

    void setId(int id) {
        if (m_id == id) {
            return;
        }
        m_id = id;
        emit idChanged();
    }
    void setAddress(const QString& address) {
        if (m_address == address) {
            return;
        }
        m_address = address;
        emit addressChanged();
    }
    void setPhone(const QString& phone) {
        if (m_phone == phone) {
            return;
        }
        m_phone = phone;
        emit phoneChanged();
    }
    void setMaritalStatus(const QString& maritalStatus) {
        if (m_maritalStatus == maritalStatus) {
            return;
        }
        m_maritalStatus = maritalStatus;
        emit maritalStatusChanged();
    }
    void setCountryCodes(const QList<int>& countryCodes) {
        m_countryCodes = countryCodes;
        emit countryCodesChanged();
    }

    int id() {
        return m_id;
    }
    QString address() {
        return m_address;
    }
    QString phone() {
        return m_phone;
    }
    QString maritalStatus() {
        return m_maritalStatus;
    }
    QList<int> countryCodes() {
        return m_countryCodes;
    }

signals:
    void idChanged();
    void addressChanged();
    void phoneChanged();
    void maritalStatusChanged();
    void countryCodesChanged();

private:
    int m_id = -1;
    QString m_address;
    QString m_phone;
    QString m_maritalStatus;
    QList<int> m_countryCodes;
};

#endif // ADDITIONALEMP_H
