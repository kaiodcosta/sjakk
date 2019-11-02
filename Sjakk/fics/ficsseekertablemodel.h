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

#ifndef FICSSEEKERTABLEMODEL_H
#define FICSSEEKERTABLEMODEL_H

#include "ficsseeker.h"
#include <QObject>
#include <QAbstractTableModel>
#include <QVector>

class FicsSeekerTableModel : public QAbstractTableModel
    {
        Q_OBJECT
    public:
        explicit FicsSeekerTableModel(QObject *parent = nullptr);
        explicit FicsSeekerTableModel(QList<FicsSeeker> seeklist, QObject *parent = nullptr);

    signals:

    public slots:

    private:
        QVector<FicsSeeker> m_seekers;

        // QAbstractItemModel interface
    public:
        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent) const override;
        QVariant data(const QModelIndex &index, int role) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role) override;
        bool setData(const QModelIndex &index, const FicsSeeker &value, int role);
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        bool insertRows(int position, int rows, const QModelIndex &parent) override;
        bool removeRows(int row, int count, const QModelIndex &parent) override;
        FicsSeeker removeSeekerByID(const int sid);
        FicsSeeker data(const QModelIndex &index) const;
        void clearRows();
        Qt::ItemFlags flags(const QModelIndex &index) const override;
    };

#endif // FICSSEEKERTABLEMODEL_H
