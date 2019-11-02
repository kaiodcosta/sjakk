/************************************************************************
Copyright 2019, Jose de Leon (a.k.a: Christian on FICS at freechess.org)

This file is part of Sjakk

Sjakk is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sjakk is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sjakk.  If not, see <https://www.gnu.org/licenses/>.
************************************************************************/

#ifndef FICSGAMETABLEMODEL_H
#define FICSGAMETABLEMODEL_H

#include "ficsgameinfo.h"
#include <QObject>
#include <QAbstractTableModel>
#include <QVector>

class FicsGameTableModel : public QAbstractTableModel
    {
        Q_OBJECT
    public:
        explicit FicsGameTableModel(QObject *parent = nullptr);

    signals:

    public slots:

    private:
        QVector<FicsGameInfo> m_gameinfos;

        // QAbstractItemModel interface
    public:
        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent) const override;
        QVariant data(const QModelIndex &index, int role) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role) override;
        bool setData(const QModelIndex &index, const FicsGameInfo &value, int role);
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        bool insertRows(int position, int rows, const QModelIndex &parent) override;
        bool removeRows(int row, int count, const QModelIndex &parent) override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        void clearRows();
        FicsGameInfo removeGameInfoByID(const int ID);
        FicsGameInfo data(const QModelIndex &index) const;
        FicsGameInfo findGameInfoByID(const int ID);

    };

#endif // FICSGAMETABLEMODEL_H
