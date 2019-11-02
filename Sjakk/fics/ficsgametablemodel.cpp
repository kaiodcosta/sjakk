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

#include "ficsgametablemodel.h"
#include <QDebug>

FicsGameTableModel::FicsGameTableModel(QObject *parent)
    : QAbstractTableModel(parent)
    {
    }

int FicsGameTableModel::rowCount(const QModelIndex &parent) const
    {
    Q_UNUSED(parent)
    return m_gameinfos.size();
    }

int FicsGameTableModel::columnCount(const QModelIndex &parent) const
    {
    Q_UNUSED(parent)
    return 7;
    }

QVariant FicsGameTableModel::data(const QModelIndex &index, int role) const
    {
    if (!index.isValid() || (index.row() >= m_gameinfos.size()) || (index.row() < 0))
        return QVariant();

    if (role == Qt::DisplayRole)
        {
        FicsGameInfo ginfo = m_gameinfos.at(index.row());

        switch (index.column())
            {
            case 0:
                return ginfo.GameID();

            case 1:
                return ginfo.WhiteRating();

            case 2:
                return ginfo.WhiteName();

            case 3:
                return ginfo.BlackRating();

            case 4:
                return ginfo.BlackName();

            case 5:
                return QString("%1 + %2").arg(ginfo.TimeMinutes()).arg(ginfo.TimeIncrement());

            case 6:
                return QString("%1 %2").arg(ginfo.IsRated() ? "rated" : "unrated").arg(ginfo.LongGameCategory());
            }
        }

    return QVariant();
    }

FicsGameInfo FicsGameTableModel::data(const QModelIndex &index) const
    {
    if (!index.isValid() || (index.row() >= m_gameinfos.size()) || (index.row() < 0))
        return FicsGameInfo();

    return m_gameinfos.at(index.row());
    }

bool FicsGameTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
    if (index.isValid() && role == Qt::EditRole)
        {
        FicsGameInfo ginfo = m_gameinfos.value(index.row());

        switch (index.column())
            {
            case 0:
                ginfo.setGameID(value.toInt());
                break;

            case 1:
                ginfo.setWhiteRating(value.toString());
                break;

            case 2:
                ginfo.setWhiteName(value.toString());
                break;

            case 3:
                ginfo.setBlackRating(value.toString());
                break;

            case 4:
                ginfo.setBlackName(value.toString());
                break;

            case 5:
                break;

            case 6:
                break;

            default:
                return false;
            }

        m_gameinfos.replace(index.row(), ginfo);
        emit(dataChanged(index, index));
        return true;
        }

    return false;
    }

bool FicsGameTableModel::setData(const QModelIndex &index, const FicsGameInfo &value, int role)
    {
    if (index.isValid() && role == Qt::EditRole)
        {
        FicsGameInfo ginfo = m_gameinfos.value(index.row());
        ginfo = value;

        if (findGameInfoByID(ginfo.GameID()).GameID() != -1)
            return false;

        m_gameinfos.replace(index.row(), ginfo);
        emit(dataChanged(index, index));
        emit layoutAboutToBeChanged();
        changePersistentIndex(index, QModelIndex());
        emit layoutChanged();
        return true;
        }

    return false;
    }

QVariant FicsGameTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return "White Rating";

            case 2:
                return "White Name";

            case 3:
                return "Black Rating";

            case 4:
                return "Black Name";

            case 5:
                return "Time";

            case 6:
                return "Type";
            }
        }

    return QVariant();
    }

bool FicsGameTableModel::insertRows(int position, int rows, const QModelIndex &parent)
    {
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        {
        FicsGameInfo ginfo;
        m_gameinfos.insert(position, ginfo);
        }

    endInsertRows();
    return true;
    }

bool FicsGameTableModel::removeRows(int row, int count, const QModelIndex &parent)
    {
    Q_UNUSED(parent);

    if (count < 1)
        return true;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int cnt = 0; (cnt < count) && (row < m_gameinfos.size()); cnt++)
        m_gameinfos.removeAt(row);

    endRemoveRows();
    return true;
    }

Qt::ItemFlags FicsGameTableModel::flags(const QModelIndex &index) const
    {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }

void FicsGameTableModel::clearRows()
    {
    removeRows(0, m_gameinfos.size(), QModelIndex());
    }

FicsGameInfo FicsGameTableModel::removeGameInfoByID(const int ID)
    {
    FicsGameInfo ginfo;
    ginfo.setGameID(ID);
    int position = m_gameinfos.indexOf(ginfo);

    if (position == -1)
        {
        ginfo.setGameID(-1);
        return ginfo;
        }

    ginfo = m_gameinfos[position];
    removeRows(position, 1, QModelIndex());
    return ginfo;
    }

FicsGameInfo FicsGameTableModel::findGameInfoByID(const int ID)
    {
    FicsGameInfo ginfo;
    ginfo.setGameID(ID);
    int position = m_gameinfos.indexOf(ginfo);

    if (position == -1)
        {
        ginfo.setGameID(-1);
        return ginfo;
        }

    ginfo = m_gameinfos[position];
    return ginfo;
    }


