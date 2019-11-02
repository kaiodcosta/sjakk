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

#include "gameflags.h"

GameFlags::GameFlags(QObject *parent) : QObject(parent)
    {
    }

GameFlags::PieceType GameFlags::ConvertToPieceType(QChar p)
    {
    if (p == "P") return GameFlags::PieceType::WhitePawn;

    if (p == "p") return GameFlags::PieceType::BlackPawn;

    if (p == "N") return GameFlags::PieceType::WhiteKnight;

    if (p == "n") return GameFlags::PieceType::BlackKnight;

    if (p == "B") return GameFlags::PieceType::WhiteBishop;

    if (p == "b") return GameFlags::PieceType::BlackBishop;

    if (p == "R") return GameFlags::PieceType::WhiteRook;

    if (p == "r") return GameFlags::PieceType::BlackRook;

    if (p == "K") return GameFlags::PieceType::WhiteKing;

    if (p == "k") return GameFlags::PieceType::BlackKing;

    if (p == "Q") return GameFlags::PieceType::WhiteQueen;

    if (p == "q") return GameFlags::PieceType::BlackQueen;

    return GameFlags::PieceType::NoPiece;
    }

GameFlags::PlayerColor GameFlags::ConvertToColor(GameFlags::PieceType piece_type)
    {
    if (piece_type > 0) return GameFlags::PlayerColor::White;

    if (piece_type < 0) return GameFlags::PlayerColor::Black;

    return GameFlags::PlayerColor::None;
    }



GameFlags::AcceptMouse GameFlags::ConvertToAcceptMouse(GameFlags::PlayerColor player_color)
    {
    return player_color == GameFlags::PlayerColor::White ? GameFlags::AcceptMouse::AcceptWhiteInput : GameFlags::AcceptMouse::AcceptBlackInput;
    }

QMap<int, QString> GameFlags::GameTypes =
    {
        {GameType::StandardChess, "Standard Chess"},
        {GameType::FischerRandom, "Fischer Random"}
    };

