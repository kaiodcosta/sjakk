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

#ifndef FICSSTYLE12_H
#define FICSSTYLE12_H

#include "../game/gameflags.h"
#include <QObject>
#include <QVector>

class FicsStyle12 : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QVector<QVector<GameFlags::PieceType>> Position READ Position WRITE setPosition)
        Q_PROPERTY(bool WhiteToMove READ WhiteToMove WRITE setWhiteToMove)
        Q_PROPERTY(int EPFile READ EPFile WRITE setEPFile)
        Q_PROPERTY(bool CanWhiteCastleShort READ CanWhiteCastleShort WRITE setCanWhiteCastleShort)
        Q_PROPERTY(bool CanWhiteCastleLong READ CanWhiteCastleLong WRITE setCanWhiteCastleLong)
        Q_PROPERTY(bool CanBlackCastleShort READ CanBlackCastleShort WRITE setCanBlackCastleShort)
        Q_PROPERTY(bool CanBlackCastleLong READ CanBlackCastleLong WRITE setCanBlackCastleLong)
        Q_PROPERTY(int HalfMoveCount READ HalfMoveCount WRITE setHalfMoveCount)
        Q_PROPERTY(int GameID READ GameID WRITE setGameID)
        Q_PROPERTY(QString WhiteName READ WhiteName WRITE setWhiteName)
        Q_PROPERTY(QString BlackName READ BlackName WRITE setBlackName)
        Q_PROPERTY(GameRelation MyRelation READ MyRelation WRITE setMyRelation)
        Q_PROPERTY(int TimeMinutes READ TimeMinutes WRITE setTimeMinutes)
        Q_PROPERTY(int TimeIncrementSeconds READ TimeIncrementSeconds WRITE setTimeIncrementSeconds)
        Q_PROPERTY(int WhiteMaterial READ WhiteMaterial WRITE setWhiteMaterial)
        Q_PROPERTY(int BlackMaterial READ BlackMaterial WRITE setBlackMaterial)
        Q_PROPERTY(int WhiteRemainingTimeSeconds READ WhiteRemainingTimeSeconds WRITE setWhiteRemainingTimeSeconds)
        Q_PROPERTY(int BlackRemainingTimeSeconds READ BlackRemainingTimeSeconds WRITE setBlackRemainingTimeSeconds)
        Q_PROPERTY(int MoveAboutToBeMade READ MoveAboutToBeMade WRITE setMoveAboutToBeMade)
        Q_PROPERTY(QString VerboseCoordinateNotationPreviousMove READ VerboseCoordinateNotationPreviousMove WRITE setVerboseCoordinateNotationPreviousMove)
        Q_PROPERTY(int TimeMinutesPreviousMove READ TimeMinutesPreviousMove WRITE setTimeMinutesPreviousMove)
        Q_PROPERTY(int TimeSecondsPreviousMove READ TimeSecondsPreviousMove WRITE setTimeSecondsPreviousMove)
        Q_PROPERTY(QString PrettyNotationPreviousMove READ PrettyNotationPreviousMove WRITE setPrettyNotationPreviousMove)
        Q_PROPERTY(bool BlackAtBottom READ BlackAtBottom WRITE setBlackAtBottom)
        Q_PROPERTY(bool ClockTicking READ ClockTicking WRITE setClockTicking)
        Q_PROPERTY(int LagTimeMilliseconds READ LagTimeMilliseconds WRITE setLagTimeMilliseconds)



    public:
        explicit FicsStyle12(QObject *parent = nullptr);
        enum GameRelation {ISOLATEDPOSITION = -3,
                           IAMOBSERVINGEXAMINED = -2,
                           IAMPLAYINGOPPONENTMOVE = -1,
                           IAMOBSERVINGPLAYED = 0,
                           IAMPLAYINGMYMOVE = 1,
                           IAMEXAMINER = 2
                          };
        Q_ENUM(GameRelation)

        QVector<QVector<GameFlags::PieceType>> Position() const;
        bool WhiteToMove() const;
        int EPFile() const;
        bool CanWhiteCastleShort() const;
        bool CanWhiteCastleLong() const;
        bool CanBlackCastleShort() const;
        bool CanBlackCastleLong() const;
        int HalfMoveCount() const;
        int GameID() const;
        QString WhiteName() const;
        QString BlackName() const;
        GameRelation MyRelation() const;
        int TimeMinutes() const;
        int TimeIncrementSeconds() const;
        int WhiteMaterial() const;
        int BlackMaterial() const;
        int WhiteRemainingTimeSeconds() const;
        int BlackRemainingTimeSeconds() const;
        int MoveAboutToBeMade() const;
        QString VerboseCoordinateNotationPreviousMove() const;
        int TimeMinutesPreviousMove() const;
        int TimeSecondsPreviousMove() const;
        QString PrettyNotationPreviousMove() const;
        bool BlackAtBottom() const;
        bool ClockTicking() const;
        int LagTimeMilliseconds() const;

        GameFlags::PlayerColor MyColor();
        bool IsMyMove();


    signals:


    public slots:
        void setPosition(QVector<QVector<GameFlags::PieceType>> Position);
        void setWhiteToMove(bool WhiteToMove);
        void setEPFile(int EPFile);
        void setCanWhiteCastleShort(bool CanWhiteCastleShort);
        void setCanWhiteCastleLong(bool CanWhiteCastleLong);
        void setCanBlackCastleShort(bool CanBlackCastleShort);
        void setCanBlackCastleLong(bool CanBlackCastleLong);
        void setHalfMoveCount(int HalfMoveCount);
        void setGameID(int GameID);
        void setWhiteName(QString WhiteName);
        void setBlackName(QString BlackName);
        void setMyRelation(GameRelation MyRelation);
        void setTimeMinutes(int TimeMinutes);
        void setTimeIncrementSeconds(int TimeIncrementSeconds);
        void setWhiteMaterial(int WhiteMaterial);
        void setBlackMaterial(int BlackMaterial);
        void setWhiteRemainingTimeSeconds(int WhiteRemainingTimeSeconds);
        void setBlackRemainingTimeSeconds(int BlackRemainingTimeSeconds);
        void setMoveAboutToBeMade(int MoveAboutToBeMade);
        void setVerboseCoordinateNotationPreviousMove(QString VerboseCoordinateNotationPreviousMove);
        void setTimeMinutesPreviousMove(int TimeMinutesPreviousMove);
        void setTimeSecondsPreviousMove(int TimeSecondsPreviousMove);
        void setPrettyNotationPreviousMove(QString PrettyNotationPreviousMove);
        void setBlackAtBottom(bool BlackAtBottom);
        void setClockTicking(bool ClockTicking);
        void setLagTimeMilliseconds(int LagTimeMilliseconds);
        void setPieceOnBoard(GameFlags::PieceType piece, int file, int rank);

    private:
        QVector<QVector<GameFlags::PieceType>> m_Position;
        bool m_WhiteToMove;
        int m_EPFile;
        bool m_CanWhiteCastleShort;
        bool m_CanWhiteCastleLong;
        bool m_CanBlackCastleShort;
        bool m_CanBlackCastleLong;
        int m_HalfMoveCount;
        int m_GameID;
        QString m_WhiteName;
        QString m_BlackName;
        GameRelation m_MyRelation;
        int m_TimeMinutes;
        int m_TimeIncrementSeconds;
        int m_WhiteMaterial;
        int m_BlackMaterial;
        int m_WhiteRemainingTimeSeconds;
        int m_BlackRemainingTimeSeconds;
        int m_MoveAboutToBeMade;
        QString m_VerboseCoordinateNotationPreviousMove;
        int m_TimeMinutesPreviousMove;
        int m_TimeSecondsPreviousMove;
        QString m_PrettyNotationPreviousMove;
        bool m_BlackAtBottom;
        bool m_ClockTicking;
        int m_LagTimeMilliseconds;
    };

#endif // FICSSTYLE12_H
