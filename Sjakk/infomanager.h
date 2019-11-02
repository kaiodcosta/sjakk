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

#ifndef INFOMANAGER_H
#define INFOMANAGER_H

#include <QObject>
#include <QMap>
#include <QtDebug>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QPersistentModelIndex>
#include <QHeaderView>
#include <QTabWidget>

#include "fics/ficsparser.h"
#include "fics/ficsseekertablemodel.h"
#include "fics/ficsgametablemodel.h"

class InfoManager : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QTableView *SeekerTable READ SeekerTable)
        Q_PROPERTY(FicsSeekerTableModel *SeekerModel READ SeekerModel)
        Q_PROPERTY(QSortFilterProxyModel *SeekerProxyModel READ SeekerProxyModel)
        Q_PROPERTY(QTableView *GameInfoTable READ GameInfoTable)
        Q_PROPERTY(FicsGameTableModel *GameInfoModel READ GameInfoModel)
        Q_PROPERTY(QSortFilterProxyModel *GameInfoProxyModel READ GameInfoProxyModel)

    public:
        explicit InfoManager(QObject *parent = nullptr);
        QTableView *SeekerTable() const;
        FicsSeekerTableModel *SeekerModel() const;
        QSortFilterProxyModel *SeekerProxyModel() const;
        QTableView *GameInfoTable() const;
        FicsGameTableModel *GameInfoModel() const;
        QSortFilterProxyModel *GameInfoProxyModel() const;

        void setSeekerTableModel(QTableView *table);
        void setGameInfoTableModel(QTableView *table);

    signals:
        void socketWriteRequest(QString data);

    public slots:
        void ficsSeekInfoEvent(FicsSeeker *seeker);
        void ficsSeekRemoveEvent(QList<int> *removelist);
        void ficsSeekClearEvent();
        void ficsGameListEvent(FicsGameInfo *ginfo);
        void ficsGameListEndEvent();
        void ficsExamListEvent(FicsGameInfo *ginfo);
        void ficsGameListClearEvent();
        void ficsGameBannerStartedEvent(FicsBannerInfo *binfo);
        void ficsGameBannerEndedEvent(FicsBannerInfo *binfo);

        void gameInfoDblClickedEvent(const QModelIndex &qmi);
        void seekInfoDblClickedEvent(const QModelIndex &qmi);
        void myGameStartedEvent();

    private:
        QTableView *m_SeekerTable;
        FicsSeekerTableModel *m_SeekerModel;
        QSortFilterProxyModel *m_SeekerProxyModel;
        QTableView *m_GameInfoTable;
        FicsGameTableModel *m_GameInfoModel;
        QSortFilterProxyModel *m_GameInfoProxyModel;
    };

#endif // INFOMANAGER_H
