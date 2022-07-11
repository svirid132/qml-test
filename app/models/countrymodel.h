#ifndef COUNTRYMODEL_H
#define COUNTRYMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "data.h"

class CountryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CountryModel(QObject *parent = nullptr);

    void setCountryDatas(const QList<CountryData>& data);
    Q_INVOKABLE void setCheck(int row, bool check);

public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Q_INVOKABLE void setCheckCounties(const QList<int>& codes);
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
