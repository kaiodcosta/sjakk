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

#include "ficsseekertablemodel.h"

FicsSeekerTableModel::FicsSeekerTableModel(QObject *parent)
    : QAbstractTableModel(parent)
    {
    }

int FicsSeekerTableModel::rowCount(const QModelIndex &parent) const
    {
    Q_UNUSED(parent);
    return m_seekers.size();
    }

int FicsSeekerTableModel::columnCount(const QModelIndex &parent) const
    {
    Q_UNUSED(parent);
    return 11;
    }

QVariant FicsSeekerTableModel::data(const QModelIndex &index, int role) const
    {
    if (!index.isValid() || (index.row() >= m_seekers.size()) || (index.row() < 0))
        return QVariant();

    if (role == Qt::DisplayRole)
        {
        FicsSeeker skr = m_seekers.at(index.row());

        switch (index.column())
            {
            case 0:
                return skr.seekerIndex();

            case 1:
                return skr.seekerFromName();

            case 2:
                return skr.seekerRating();

            case 3:
                return skr.seekerTimeControl();

            case 4:
                return skr.seekerTimeIncrement();

            case 5:
                return QString("%1 %2").arg(skr.seekerIsRated() ? "rated" : "unrated").arg(skr.seekerGameType());

            case 6:
                return QString("%1 %2").arg(skr.seekerStartAutomatic() ? "" : "manual").arg(skr.seekerFormulaChecked() ? "formula" : "");

            case 7:
                return skr.seekerIsRated();

            case 8:
                return skr.seekerGameType();

            case 9:
                return skr.seekerStartAutomatic();

            case 10:
                return skr.seekerFormulaChecked();
            }
        }

    return QVariant();
    }

bool FicsSeekerTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
    if (index.isValid() && role == Qt::EditRole)
        {
        int row = index.row();
        FicsSeeker skr = m_seekers.value(row);

        switch (index.column())
            {
            case 0:
                skr.setSeekerIndex(value.toInt());
                break;

            case 1:
                skr.setSeekerFromName(value.toString());
                break;

            case 2:
                skr.setSeekerRating(value.toInt());
                break;

            case 3:
                skr.setSeekerTimeControl(value.toInt());
                break;

            case 4:
                skr.setSeekerTimeIncrement(value.toInt());
                break;

            case 5:
                break;

            case 6:
                break;

            case 7:
                skr.setSeekerIsRated(value.toBool());
                break;

            case 8:
                skr.setSeekerGameType(value.toString());
                break;

            case 9:
                skr.setSeekerStartAutomatic(value.toBool());
                break;

            case 10:
                skr.setSeekerFormulaChecked(value.toBool());
                break;

            default:
                return false;
            }

        m_seekers.replace(row, skr);
        emit(dataChanged(index, index));
        return true;
        }

    return false;
    }

bool FicsSeekerTableModel::setData(const QModelIndex &index, const FicsSeeker &value, int role)
    {
    if (index.isValid() && role == Qt::EditRole)
        {
        int row = index.row();
        FicsSeeker seeker = m_seekers.value(row);
        seeker = value;
        m_seekers.replace(row, seeker);
        emit(dataChanged(index, index));
        emit layoutAboutToBeChanged();
        changePersistentIndex(index, QModelIndex());
        emit layoutChanged();
        return true;
        }

    return false;
    }

QVariant FicsSeekerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        {
        switch (section)
            {
            case 0:
                return "ID";

            case 1:
                return "Name";

            case 2:
                return "Rating";

            case 3:
                return "Time";

            case 4:
                return "Increment";

            case 5:
                return "Type";

            case 6:
                return "Requires";

            case 7:
                return "Is Rated";

            case 8:
                return "Game Type";

            case 9:
                return "Autostart";

            case 10:
                return "Formula";
            }
        }

    return QVariant();
    }

bool FicsSeekerTableModel::insertRows(int position, int rows, const QModelIndex &parent)
    {
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        {
        FicsSeeker skr;
        m_seekers.insert(position, skr);
        }

    endInsertRows();
    return true;
    }

bool FicsSeekerTableModel::removeRows(int row, int count, const QModelIndex &parent)
    {
    (void)parent;

    if (count < 1)
        return true;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int cnt = 0; (cnt < count) && (row < m_seekers.size()); cnt++)
        m_seekers.removeAt(row);

    endRemoveRows();
    return true;
    }

FicsSeeker FicsSeekerTableModel::removeSeekerByID(const int ID)
    {
    FicsSeeker skr;
    skr.setSeekerIndex(ID);
    int position = m_seekers.indexOf(skr);

    if (position == -1)
        return skr;

    skr = m_seekers[position];
    removeRows(position, 1, QModelIndex());
    return skr;
    }

FicsSeeker FicsSeekerTableModel::data(const QModelIndex &index) const
    {
    if (!index.isValid() || (index.row() >= m_seekers.size()) || (index.row() < 0))
        return FicsSeeker();

    return m_seekers.at(index.row());
    }

void FicsSeekerTableModel::clearRows()
    {
    removeRows(0, m_seekers.size(), QModelIndex());
    }

Qt::ItemFlags FicsSeekerTableModel::flags(const QModelIndex &index) const
    {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
