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

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QMap>
#include <QTabWidget>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QPersistentModelIndex>
#include <QHeaderView>
#include <QSoundEffect>
#include <QMessageBox>
#include "configsettings.h"
#include "../infomanager.h"
#include "gameboard.h"
#include "../fics/ficsseeker.h"
#include "../fics/ficsgameinfo.h"
#include "../soundmanager.h"

class GameManager : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QTabWidget *GameTabs READ GameTabs WRITE setGameTabs)

    private:
        QTabWidget *m_GameTabs;
        QMap<int, GameBoard *> gameid_board_map;
        QMap<int, int> gameid_tabindex_map;
        InfoManager *m_InfoMgr;
        SoundManager *_soundManager;

        //void AddGame(int gameid, FicsStyle12 *gdata);
        //void UpdateGame(int gameid, FicsStyle12 *gdata);
        void EndGame(int gameid, FicsBannerInfo *binfo);

    public:
        explicit GameManager(QObject *parent = nullptr);
        void setInfoManager(InfoManager *imgr);
        QTabWidget *GameTabs() const;

    signals:
        void signalGameMoveInvalid();
        void signalSocketWriteRequest(QString data);
        void signalMyGameStarted();
        void signalMyGameOver();


    public slots:
        void ficsGameBannerEndedEvent(FicsBannerInfo *binfo);
        void ficsGameListItemEvent(FicsGameInfo *ginfo);
        void ficsStyle12Event(FicsStyle12 *gdata);
        void gameTabClosedEvent(int index);
        void serverDisconnect();
        void chessMoveEvent(int fromFile, int fromRank, int toFile, int toRank);
        void testerAddBoard();

        void setGameTabs(QTabWidget *GameTabs);

        void Resign();
        void RequestAdjourn();
        void RequestDraw();
        void RequestAbort();

    };

#endif // GAMEMANAGER_H
