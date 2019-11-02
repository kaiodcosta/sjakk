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

#ifndef GAMEFLAGS_H
#define GAMEFLAGS_H

#include <QObject>
#include <QMap>

class GameFlags : public QObject
    {
        Q_OBJECT
    public:
        explicit GameFlags(QObject *parent = nullptr);
        enum AcceptMouse : uint
            {
            AcceptWhiteInput,
            AcceptBlackInput,
            AcceptAny,
            AcceptNone
            };
        Q_ENUM(AcceptMouse)

        enum PieceType
            {
            NoPiece = 0,
            WhitePawn = 1, WhiteKing = 2, WhiteQueen = 3, WhiteBishop = 4, WhiteKnight = 5, WhiteRook = 6,
            BlackPawn = -1, BlackKing = -2, BlackQueen = -3, BlackBishop = -4, BlackKnight = -5, BlackRook = -6
            };
        Q_ENUM(PieceType)

        enum GameType : int
            {
            StandardChess = 0,
            FischerRandom = 1
            };
        Q_ENUM(GameType)

        enum PlayerColor
            {
            White,
            Black,
            None
            };
        Q_ENUM(PlayerColor)

        enum GameClose
            {
            CloseAllowed,
            CloseNotAllowed,
            PromptFirst
            };
        Q_ENUM(GameClose)



        static QMap<int, QString> GameTypes;
        static GameFlags::PieceType ConvertToPieceType(QChar p);
        static GameFlags::PlayerColor ConvertToColor(GameFlags::PieceType piece_type);
        static GameFlags::AcceptMouse ConvertToAcceptMouse(GameFlags::PlayerColor player_color);


    signals:

    public slots:
    };

#endif // GAMEFLAGS_H
