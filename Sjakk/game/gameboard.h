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

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QChar>
#include <QString>
#include "chessclock.h"
#include "gameflags.h"
#include "chessboard.h"
#include "../configsettings.h"
#include "../fics/ficsstyle12.h"
#include "../fics/ficsgameinfo.h"
#include "../fics/ficsbannerinfo.h"

namespace Ui
{
class GameBoard;
}

class GameBoard : public QWidget
    {
        Q_OBJECT
        Q_PROPERTY(FicsStyle12 *PositionData READ PositionData WRITE setPositionData)
        Q_PROPERTY(GameFlags::GameClose CanClose READ CanClose WRITE setCanClose)

    public:
        explicit GameBoard(QWidget *parent = nullptr);
        ~GameBoard();
        FicsStyle12 *PositionData() const;

        void StopClocks();
        GameFlags::GameClose CanClose() const;

        bool GameOver() const;
        void setGameOver(QString reason);

    public slots:
        void chessMoveEvent(GameFlags::PieceType source_piece, int fromFile, int fromRank, GameFlags::PieceType target_piece, int toFile, int toRank);
        void setPositionData(FicsStyle12 *PositionData);
        void FicsStyle12Event(FicsStyle12 *fics_style12, bool IsUpdate = true);
        void setCanClose(GameFlags::GameClose CanClose);
        void updateGameInfo(FicsGameInfo *game_info);
        void updatePlayerInfo(FicsGameInfo *game_info);
        void setGameOver(FicsBannerInfo *banner_info);


        bool IAmPlayingGame(FicsStyle12::GameRelation relation);

    signals:
        void signalChessMove(int fromFile, int fromRank, int toFile, int toRank);
        void signalGameOver(bool iam_playing);

    private:
        Ui::GameBoard *ui;
        FicsStyle12 *m_PositionData;
        QList<QString> previous_highlighted;

        ConfigSettings *options;

        void loadPieceSet();


        void updateStrengths();
        void updateClocks();
        void updateLastMoved();
        void updateLag();


        GameFlags::GameClose m_CanClose;
        bool m_GameOver;
    };

#endif // GAMEBOARD_H
