#include "countrytable.h"

CountryTable::CountryTable(QObject *parent)
    : QAbstractTableModel{parent}
{
    QList<SQLite::Country> data = sqliteManager.execSelectCountries();
    std::for_each(data.begin(), data.end(), [this](const SQLite::Country& country) {
        CountryData countryHandled;
        countryHandled.code = country.code;
        countryHandled.country = country.name;

        countryDatas.append(countryHandled);
    });

    std::sort(countryDatas.begin(), countryDatas.end(), [](const CountryData& x, const CountryData& y) {
        return x.code < y.code;
    });
}

void CountryTable::setCheck(int row, bool check)
{
    QModelIndex index = this->index(row, 2);
    this->setData(index, check, Qt::EditRole);
    emit this->dataChanged(index, index);
}

int CountryTable::rowCount(const QModelIndex &parent) const
{
    return countryDatas.size();
}

int CountryTable::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant CountryTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    // Для qml
    if (role >= Qt::UserRole) {
        int column = role - Qt::UserRole;
        if (column == 2) {
            return data(this->index(index.row(), column), Qt::CheckStateRole);
        }
        return data(this->index(index.row(), column), Qt::DisplayRole);
    }

    int row = index.row();
    switch(role) {
    case Qt::DisplayRole: {
        switch (index.column()) {
        case 0: {
            return countryDatas.at(row).code;
        }
        case 1: {
            return countryDatas.at(row).country;
        }
        }
    }
    case Qt::CheckStateRole: {
        switch (index.column()) {
        case 2: {
            if ( countryDatas.at(row).isCheck ) {
                return Qt::Checked;
            } else {
                return Qt::Unchecked;
            }
        }
        }
    }
    }


    return QVariant();
}


QHash<int, QByteArray> CountryTable::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[codeRole] = "code";
    roles[nameRole] = "name";
    roles[isCheckRole] = "isCheck";

    return roles;
}


Qt::ItemFlags CountryTable::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == 2) {
        flags = flags & Qt::ItemIsUserCheckable;
    }

    return flags;
}


bool CountryTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() == 2) {
        int row = index.row();
        countryDatas[row].isCheck = value.toBool();
        return true;
    }

    return false;
}

void CountryTable::setCodeCountriesChecked(const QList<int>& codes)
{
    QList<int> sortCodes = codes;
    std::sort(sortCodes.begin(), sortCodes.end());

    for (int i = 0, a = 0; i < countryDatas.size(); ++i) {
        auto inx = index(i, 2);
        this->setData(inx, false);
    }

    for (int i = 0, a = 0; i < countryDatas.size() && a < codes.size(); ++i) {
        if (countryDatas.at(i).code == codes.at(a)) {
            auto inx = index(i, 2);
            this->setData(inx, true);
            ++a;
        }
    }

    auto leftRightIndex = this->index(0, 2);
    int lastRow = countryDatas.size() - 1;
    auto rightBottomIndex = this->index(lastRow, 2);

    emit this->dataChanged(leftRightIndex, rightBottomIndex);
    emit codeCountriesCheckedChanged();
}
