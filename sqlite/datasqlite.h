#ifndef DATASQLITE_H
#define DATASQLITE_H

#include <QDebug>
#include <QList>
#include <QString>

struct Additionally {
    int id = -1;
    QString address = "";
    QString phone = "";
    QString maritalStatus = "";
    QList<int> codeCountries = QList<int>();
    bool operator==(const Additionally& right) const {
        qDebug() << "this->codeCountries" << this->codeCountries << "right.codeCountries" << right.codeCountries;
        if (this->codeCountries.size() != right.codeCountries.size()) return false;
        bool isCodeCountries = true;
        QList<int> lhsCodeCts = this->codeCountries;
        QList<int> rhsCodeCts = right.codeCountries;
        std::sort(lhsCodeCts.begin(), lhsCodeCts.end());
        std::sort(rhsCodeCts.begin(), rhsCodeCts.end());
        for (int i = 0; i < lhsCodeCts.size() && i < rhsCodeCts.size(); ++i) {
            if (lhsCodeCts.at(i) != rhsCodeCts.at(i)) {
                isCodeCountries = false;
            }
        }
        qDebug() << "isCodeCountries:" << isCodeCountries;
        return ( this->id == right.id &&
                 this->address == right.address &&
                 this->phone== right.phone &&
                 this->maritalStatus == right.maritalStatus &&
                 isCodeCountries);
    }
};

struct Country {
    int code;
    QString name;
    bool operator==(const Country& rhs) const {
        return ( this->code == rhs.code &&
                 this->name == rhs.name);
    };
};

struct Employee {
    int id = -1;
    QString firstName;
    QString lastName;
    int additionally_id;
    bool operator==(const Employee& rhs) const {
        return ( this->id == rhs.id &&
                 this->firstName == rhs.firstName &&
                 this->lastName == rhs.lastName);
    };
};

#endif // DATASQLITE_H
