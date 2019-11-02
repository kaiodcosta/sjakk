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

#include "gamemanager.h"

GameManager::GameManager(QObject *parent) : QObject(parent)
    {
    _soundManager = new SoundManager(this);
    }

void GameManager::setInfoManager(InfoManager *imgr)
    {
    m_InfoMgr = imgr;
    }

QTabWidget *GameManager::GameTabs() const
    {
    return m_GameTabs;
    }

void GameManager::ficsGameBannerEndedEvent(FicsBannerInfo *binfo)
    {
    if (gameid_board_map.contains(binfo->GameID()))
        {
        GameBoard *board = gameid_board_map[binfo->GameID()];
        board->setGameOver(binfo);
        //_soundManager->PlaySoundEfx("game_over");

        if (board->IAmPlayingGame(board->PositionData()->MyRelation()))
            {
            emit signalMyGameOver();
            emit signalSocketWriteRequest("iset seekinfo 1");
            }
        }
    }

void GameManager::ficsGameListItemEvent(FicsGameInfo *ginfo)
    {
    GameBoard *game_board;
    int gameid = ginfo->GameID();

    if (gameid_board_map.contains(gameid))
        {
        game_board = gameid_board_map[gameid];
        game_board->updateGameInfo(ginfo);
        game_board->updatePlayerInfo(ginfo);
        }
    }

void GameManager::ficsStyle12Event(FicsStyle12 *gdata)
    {
    GameBoard *game_board;
    int gameid = gdata->GameID();
    _soundManager->PlaySoundEfx("piece_moved");

    if (gameid_board_map.contains(gameid))
        {
        game_board = gameid_board_map[gameid];
        game_board->FicsStyle12Event(gdata, true);
        }
    else
        {
        game_board = new GameBoard();
        gameid_board_map.insert(gameid, game_board);
        m_GameTabs->addTab(game_board, QString("[%1] %2 vs %3").arg(gameid).arg(gdata->WhiteName()).arg(gdata->BlackName()));
        game_board->FicsStyle12Event(gdata, false);
        connect(game_board, &GameBoard::signalChessMove, this, &GameManager::chessMoveEvent);
        m_GameTabs->setCurrentWidget(game_board);
        emit signalSocketWriteRequest(QString("game %1").arg(gameid));

        if (game_board->IAmPlayingGame(gdata->MyRelation()))
            {
            emit signalMyGameStarted();
            emit signalSocketWriteRequest("iset seekinfo 0");
            }
        }
    }

void GameManager::gameTabClosedEvent(int index)
    {
    GameBoard *gb = qobject_cast<GameBoard *>(m_GameTabs->widget(index));

    if (gb == nullptr)
        return;

    int gameid = gb->PositionData()->GameID();

    if (gameid == -1)
        return;

    QString close_command;
    QString prompt_query;

    switch (gb->PositionData()->MyRelation())
        {
        case FicsStyle12::ISOLATEDPOSITION:
            // Nothing to do here
            break;

        case FicsStyle12::IAMPLAYINGMYMOVE:
        case FicsStyle12::IAMPLAYINGOPPONENTMOVE:
            close_command = QString("resign").arg(gameid);
            prompt_query = QString("Do you want to resign this game?");
            break;

        case FicsStyle12::IAMEXAMINER:
        case FicsStyle12::IAMOBSERVINGEXAMINED:
        case FicsStyle12::IAMOBSERVINGPLAYED:
            close_command = QString("unobserve %1").arg(gameid);
            break;
        }

    switch (gb->CanClose())
        {
        case GameFlags::CloseAllowed:
            emit signalSocketWriteRequest(close_command);
            break;

        case GameFlags::CloseNotAllowed:
            return;

        case GameFlags::PromptFirst:
            QMessageBox::StandardButton message_button;
            message_button = QMessageBox::question(m_GameTabs->widget(index), "Are you sure?",
                                                   "Do you want to resign this game?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

            switch (message_button)
                {
                case QMessageBox::Yes:
                    emit signalSocketWriteRequest(QString("resign"));
                    break;

                default:
                    return;
                }

            break;
        }

    gameid_board_map.remove(gameid);
    gameid_tabindex_map.remove(gameid);
    m_GameTabs->removeTab(index);
    }

void GameManager::serverDisconnect()
    {
    foreach (GameBoard *gb, gameid_board_map)
        gb->setGameOver("server disconnect");

    // Just make one sound for server disconnect
    // TODO: replace with server disconnect sound
    //_soundManager->PlaySoundEfx("game_over");
    }

void GameManager::chessMoveEvent(int fromFile, int fromRank, int toFile, int toRank)
    {
    QString fromSq = QString("%1%2").arg(QChar('a' + fromFile)).arg(fromRank + 1);
    QString toSq = QString("%1%2").arg(QChar('a' + toFile)).arg(toRank + 1);
    QString data(fromSq + toSq);
    emit signalSocketWriteRequest(data);
    }

void GameManager::testerAddBoard()
    {
    GameBoard *gb = new GameBoard();
    m_GameTabs->addTab(gb, "Test Tab");
    }

void GameManager::setGameTabs(QTabWidget *GameTabs)
    {
    m_GameTabs = GameTabs;
    }

void GameManager::Resign()
    {
    QString data("resign");
    emit signalSocketWriteRequest(data);
    }

void GameManager::RequestAdjourn()
    {
    QString data("adjourn");
    emit signalSocketWriteRequest(data);
    }

void GameManager::RequestDraw()
    {
    QString data("draw");
    emit signalSocketWriteRequest(data);
    }

void GameManager::RequestAbort()
    {
    QString data("abort");
    emit signalSocketWriteRequest(data);
    }
