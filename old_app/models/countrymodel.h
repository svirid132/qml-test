#ifndef COUNTRYMODEL_H
#define COUNTRYMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "data.h"

/*
 * Класс предоставляет модель посещенных стран
 * */

class CountryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CountryModel(QObject *parent = nullptr);

    /**
     * @brief setCountryDatas - Вставка всех доступных стран
     * @param data - данные
     */
    void setCountryDatas(const QList<CountryData>& data);
    //Измение выбора check для страны. Посещал или нет сотрудник страну.
    /**
     * @brief setCheck - выбор страны. Изменение check страны.
     * @param row - строка странны
     * @param check - измениен посещения страны
     */
    Q_INVOKABLE void setCheck(int row, bool check);

public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    //
    /**
     * @brief setCheckCounties - Вставка всех посещенных стран. Меняется только check.
     * @param codes - коды стран.
     */
    Q_INVOKABLE void setCheckCounties(const QList<int>& codes);
    /**
     * @brief getCheckCounties - Получить выбранные страны check.
     * @return Возвращает коды стран.
     */
    Q_INVOKABLE QList<int> getCheckCounties();

private:
    QList<CountryData> countryDatas;
    enum CountryRoles {
        codeRole = Qt::UserRole,
        nameRole = Qt::UserRole + 1,
        isCheckRole = Qt::UserRole + 2
    };
};

#endif // COUNTRYMODEL_H
