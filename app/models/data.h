#ifndef DATA_H
#define DATA_H

#include <QString>

//Структура для модели countrymodel
struct CountryData {
    int code;
    QString country;
    bool isCheck = false;
};

#endif // DATA_H
