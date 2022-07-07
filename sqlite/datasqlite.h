#ifndef DATASQLITE_H
#define DATASQLITE_H

#include <QList>
#include <QString>

struct Additionally {
    int id = -1;
    QString address = "";
    QString phone = "";
    QString maritalStatus = "";
    QList<int> codeCountries = QList<int>();
};

struct Country {
    int code;
    QString name;
};

struct Employee {
    int id = -1;
    QString firstName;
    QString lastName;
    int additionally_id;
};

#endif // DATASQLITE_H
