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

#include "ficsstyle12.h"

FicsStyle12::FicsStyle12(QObject *parent) : QObject(parent)
    {
    m_Position.clear();
    m_Position.resize(8);

    for (int i = 0; i < 8; i++)
        m_Position[i].resize(8);

    for (int i = 0; i < 8; i++)
        for (int r = 0; r < 8; r++)
            m_Position[i][r] = GameFlags::NoPiece;
    }

QVector<QVector<GameFlags::PieceType> > FicsStyle12::Position() const
    {
    return m_Position;
    }

bool FicsStyle12::WhiteToMove() const
    {
    return m_WhiteToMove;
    }

int FicsStyle12::EPFile() const
    {
    return m_EPFile;
    }

bool FicsStyle12::CanWhiteCastleShort() const
    {
    return m_CanWhiteCastleShort;
    }

bool FicsStyle12::CanWhiteCastleLong() const
    {
    return m_CanWhiteCastleLong;
    }

bool FicsStyle12::CanBlackCastleShort() const
    {
    return m_CanBlackCastleShort;
    }

bool FicsStyle12::CanBlackCastleLong() const
    {
    return m_CanBlackCastleLong;
    }

int FicsStyle12::HalfMoveCount() const
    {
    return m_HalfMoveCount;
    }

int FicsStyle12::GameID() const
    {
    return m_GameID;
    }

QString FicsStyle12::WhiteName() const
    {
    return m_WhiteName;
    }

QString FicsStyle12::BlackName() const
    {
    return m_BlackName;
    }

FicsStyle12::GameRelation FicsStyle12::MyRelation() const
    {
    return m_MyRelation;
    }

int FicsStyle12::TimeMinutes() const
    {
    return m_TimeMinutes;
    }

int FicsStyle12::TimeIncrementSeconds() const
    {
    return m_TimeIncrementSeconds;
    }

int FicsStyle12::WhiteMaterial() const
    {
    return m_WhiteMaterial;
    }

int FicsStyle12::BlackMaterial() const
    {
    return m_BlackMaterial;
    }

int FicsStyle12::WhiteRemainingTimeSeconds() const
    {
    return m_WhiteRemainingTimeSeconds;
    }

int FicsStyle12::BlackRemainingTimeSeconds() const
    {
    return m_BlackRemainingTimeSeconds;
    }

int FicsStyle12::MoveAboutToBeMade() const
    {
    return m_MoveAboutToBeMade;
    }

QString FicsStyle12::VerboseCoordinateNotationPreviousMove() const
    {
    return m_VerboseCoordinateNotationPreviousMove;
    }

int FicsStyle12::TimeMinutesPreviousMove() const
    {
    return m_TimeMinutesPreviousMove;
    }

int FicsStyle12::TimeSecondsPreviousMove() const
    {
    return m_TimeSecondsPreviousMove;
    }

QString FicsStyle12::PrettyNotationPreviousMove() const
    {
    return m_PrettyNotationPreviousMove;
    }

bool FicsStyle12::BlackAtBottom() const
    {
    return m_BlackAtBottom;
    }

bool FicsStyle12::ClockTicking() const
    {
    return m_ClockTicking;
    }

int FicsStyle12::LagTimeMilliseconds() const
    {
    return m_LagTimeMilliseconds;
    }

GameFlags::PlayerColor FicsStyle12::MyColor()
    {
    switch (MyRelation())
        {
        case FicsStyle12::IAMPLAYINGMYMOVE:
            if (WhiteToMove()) return GameFlags::PlayerColor::White;
            else return GameFlags::PlayerColor::Black;

        case FicsStyle12::IAMPLAYINGOPPONENTMOVE:
            if (WhiteToMove()) return GameFlags::PlayerColor::Black;
            else return GameFlags::PlayerColor::White;

        default:
            return GameFlags::PlayerColor::None;
        }
    }

bool FicsStyle12::IsMyMove()
    {
    return FicsStyle12::GameRelation::IAMPLAYINGMYMOVE == MyRelation();
    }

void FicsStyle12::setPosition(QVector<QVector<GameFlags::PieceType> > Position)
    {
    if (m_Position == Position)
        return;

    m_Position = Position;
    }

void FicsStyle12::setWhiteToMove(bool WhiteToMove)
    {
    if (m_WhiteToMove == WhiteToMove)
        return;

    m_WhiteToMove = WhiteToMove;
    }

void FicsStyle12::setEPFile(int EPFile)
    {
    if (m_EPFile == EPFile)
        return;

    m_EPFile = EPFile;
    }

void FicsStyle12::setCanWhiteCastleShort(bool CanWhiteCastleShort)
    {
    if (m_CanWhiteCastleShort == CanWhiteCastleShort)
        return;

    m_CanWhiteCastleShort = CanWhiteCastleShort;
    }

void FicsStyle12::setCanWhiteCastleLong(bool CanWhiteCastleLong)
    {
    m_CanWhiteCastleLong = CanWhiteCastleLong;
    }

void FicsStyle12::setCanBlackCastleShort(bool CanBlackCastleShort)
    {
    m_CanBlackCastleShort = CanBlackCastleShort;
    }

void FicsStyle12::setCanBlackCastleLong(bool CanBlackCastleLong)
    {
    m_CanBlackCastleLong = CanBlackCastleLong;
    }

void FicsStyle12::setHalfMoveCount(int HalfMoveCount)
    {
    m_HalfMoveCount = HalfMoveCount;
    }

void FicsStyle12::setGameID(int GameID)
    {
    m_GameID = GameID;
    }

void FicsStyle12::setWhiteName(QString WhiteName)
    {
    m_WhiteName = WhiteName;
    }

void FicsStyle12::setBlackName(QString BlackName)
    {
    m_BlackName = BlackName;
    }

void FicsStyle12::setMyRelation(FicsStyle12::GameRelation MyRelation)
    {
    m_MyRelation = MyRelation;
    }

void FicsStyle12::setTimeMinutes(int TimeMinutes)
    {
    m_TimeMinutes = TimeMinutes;
    }

void FicsStyle12::setTimeIncrementSeconds(int TimeIncrementSeconds)
    {
    m_TimeIncrementSeconds = TimeIncrementSeconds;
    }

void FicsStyle12::setWhiteMaterial(int WhiteMaterial)
    {
    m_WhiteMaterial = WhiteMaterial;
    }

void FicsStyle12::setBlackMaterial(int BlackMaterial)
    {
    m_BlackMaterial = BlackMaterial;
    }

void FicsStyle12::setWhiteRemainingTimeSeconds(int WhiteRemainingTimeSeconds)
    {
    m_WhiteRemainingTimeSeconds = WhiteRemainingTimeSeconds;
    }

void FicsStyle12::setBlackRemainingTimeSeconds(int BlackRemainingTimeSeconds)
    {
    m_BlackRemainingTimeSeconds = BlackRemainingTimeSeconds;
    }

void FicsStyle12::setMoveAboutToBeMade(int MoveAboutToBeMade)
    {
    m_MoveAboutToBeMade = MoveAboutToBeMade;
    }

void FicsStyle12::setVerboseCoordinateNotationPreviousMove(QString VerboseCoordinateNotationPreviousMove)
    {
    m_VerboseCoordinateNotationPreviousMove = VerboseCoordinateNotationPreviousMove;
    }

void FicsStyle12::setTimeMinutesPreviousMove(int TimeMinutesPreviousMove)
    {
    m_TimeMinutesPreviousMove = TimeMinutesPreviousMove;
    }

void FicsStyle12::setTimeSecondsPreviousMove(int TimeSecondsPreviousMove)
    {
    m_TimeSecondsPreviousMove = TimeSecondsPreviousMove;
    }

void FicsStyle12::setPrettyNotationPreviousMove(QString PrettyNotationPreviousMove)
    {
    m_PrettyNotationPreviousMove = PrettyNotationPreviousMove;
    }

void FicsStyle12::setBlackAtBottom(bool BlackAtBottom)
    {
    m_BlackAtBottom = BlackAtBottom;
    }

void FicsStyle12::setClockTicking(bool ClockTicking)
    {
    m_ClockTicking = ClockTicking;
    }

void FicsStyle12::setLagTimeMilliseconds(int LagTimeMilliseconds)
    {
    m_LagTimeMilliseconds = LagTimeMilliseconds;
    }

void FicsStyle12::setPieceOnBoard(GameFlags::PieceType piece, int file, int rank)
    {
    m_Position[file][rank] = piece;
    }
