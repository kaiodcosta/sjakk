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

#include "infomanager.h"

InfoManager::InfoManager(QObject *parent) :
    QObject(parent),
    m_SeekerModel(new FicsSeekerTableModel()),
    m_SeekerProxyModel(new QSortFilterProxyModel()),
    m_GameInfoModel(new FicsGameTableModel()),
    m_GameInfoProxyModel(new QSortFilterProxyModel())
    {
    }

QTableView *InfoManager::SeekerTable() const
    {
    return m_SeekerTable;
    }

FicsSeekerTableModel *InfoManager::SeekerModel() const
    {
    return m_SeekerModel;
    }

QSortFilterProxyModel *InfoManager::SeekerProxyModel() const
    {
    return m_SeekerProxyModel;
    }

QTableView *InfoManager::GameInfoTable() const
    {
    return m_GameInfoTable;
    }

FicsGameTableModel *InfoManager::GameInfoModel() const
    {
    return m_GameInfoModel;
    }

QSortFilterProxyModel *InfoManager::GameInfoProxyModel() const
    {
    return m_GameInfoProxyModel;
    }

void InfoManager::setSeekerTableModel(QTableView *table)
    {
    m_SeekerTable = table;
    m_SeekerProxyModel->setSourceModel(m_SeekerModel);
    m_SeekerProxyModel->setSortCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
    m_SeekerTable->setModel(m_SeekerProxyModel);
    m_SeekerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_SeekerTable->horizontalHeader()->setStretchLastSection(true);
    m_SeekerTable->verticalHeader()->hide();
    m_SeekerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_SeekerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_SeekerTable->setSortingEnabled(true);
    }

void InfoManager::setGameInfoTableModel(QTableView *table)
    {
    m_GameInfoTable = table;
    m_GameInfoProxyModel->setSourceModel(m_GameInfoModel);
    m_GameInfoProxyModel->setSortCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
    m_GameInfoTable->setModel(m_GameInfoProxyModel);
    m_GameInfoTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_GameInfoTable->horizontalHeader()->setStretchLastSection(true);
    m_GameInfoTable->verticalHeader()->hide();
    m_GameInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_GameInfoTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_GameInfoTable->setSortingEnabled(true);
    connect(m_GameInfoTable, &QTableView::doubleClicked, this, &InfoManager::gameInfoDblClickedEvent);
    connect(m_SeekerTable, &QTableView::doubleClicked, this, &InfoManager::seekInfoDblClickedEvent);
    }

void InfoManager::ficsSeekInfoEvent(FicsSeeker *seeker)
    {
    m_SeekerModel->insertRows(0, 1, QModelIndex());
    QModelIndex index = m_SeekerModel->index(0, 0, QModelIndex());
    m_SeekerModel->setData(index, *seeker, Qt::EditRole);
    }

void InfoManager::ficsSeekRemoveEvent(QList<int> *removelist)
    {
    foreach (int sid, *removelist)
        m_SeekerModel->removeSeekerByID(sid);
    }

void InfoManager::ficsSeekClearEvent()
    {
    m_SeekerModel->clearRows();
    }

void InfoManager::ficsGameListEvent(FicsGameInfo *ginfo)
    {
    m_GameInfoModel->insertRows(0, 1, QModelIndex());
    QModelIndex index = m_GameInfoModel->index(0, 0, QModelIndex());
    m_GameInfoModel->setData(index, *ginfo, Qt::EditRole);
    }

void InfoManager::ficsGameListEndEvent()
    {
    // Nothing to do
    }

void InfoManager::ficsExamListEvent(FicsGameInfo *ginfo)
    {
    this->ficsGameListEvent(ginfo);
    }

void InfoManager::ficsGameListClearEvent()
    {
    m_GameInfoModel->clearRows();
    }

void InfoManager::ficsGameBannerStartedEvent(FicsBannerInfo *binfo)
    {
    emit socketWriteRequest(QString("game %1").arg(binfo->GameID()));
    }

void InfoManager::ficsGameBannerEndedEvent(FicsBannerInfo *binfo)
    {
    m_GameInfoModel->removeGameInfoByID(binfo->GameID());
    }

void InfoManager::gameInfoDblClickedEvent(const QModelIndex &qmi)
    {
    QModelIndex srcindex = m_GameInfoProxyModel->mapToSource(qmi);
    FicsGameInfo ginfo = m_GameInfoModel->data(srcindex);

    if (ginfo.GameID() == -1)
        return;

    qDebug() << "observe request for " << ginfo.GameID();
    emit socketWriteRequest(QString("observe %1").arg(ginfo.GameID()));
    }

void InfoManager::seekInfoDblClickedEvent(const QModelIndex &qmi)
    {
    QModelIndex srcindex = m_SeekerProxyModel->mapToSource(qmi);
    FicsSeeker seekinfo = m_SeekerModel->data(srcindex);
    qDebug() << "play request for " << seekinfo.seekerIndex();
    emit socketWriteRequest(QString("play %1").arg(seekinfo.seekerIndex()));
    }

void InfoManager::myGameStartedEvent()
    {
    m_SeekerModel->clearRows();
    }
