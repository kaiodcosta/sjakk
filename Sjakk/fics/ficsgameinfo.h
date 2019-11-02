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

#ifndef FICSGAMEINFO_H
#define FICSGAMEINFO_H

#include <QObject>

class FicsGameInfo : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(int GameID READ GameID WRITE setGameID NOTIFY GameIDChanged)
        Q_PROPERTY(QString WhiteRating READ WhiteRating WRITE setWhiteRating NOTIFY WhiteRatingChanged)
        Q_PROPERTY(QString BlackRating READ BlackRating WRITE setBlackRating NOTIFY BlackRatingChanged)
        Q_PROPERTY(QString WhiteName READ WhiteName WRITE setWhiteName NOTIFY WhiteNameChanged)
        Q_PROPERTY(QString BlackName READ BlackName WRITE setBlackName NOTIFY BlackNameChanged)
        Q_PROPERTY(bool IsPrivate READ IsPrivate WRITE setIsPrivate NOTIFY IsPrivateChanged)
        Q_PROPERTY(QString GameCategory READ GameCategory WRITE setGameCategory NOTIFY GameCategoryChanged)
        Q_PROPERTY(bool IsRated READ IsRated WRITE setIsRated NOTIFY IsRatedChanged)
        Q_PROPERTY(int TimeMinutes READ TimeMinutes WRITE setTimeMinutes NOTIFY TimeMinutesChanged)
        Q_PROPERTY(int TimeIncrement READ TimeIncrement WRITE setTimeIncrement NOTIFY TimeIncrementChanged)
        Q_PROPERTY(QString WhiteClockTime READ WhiteClockTime WRITE setWhiteClockTime NOTIFY WhiteClockTimeChanged)
        Q_PROPERTY(QString BlackClockTime READ BlackClockTime WRITE setBlackClockTime NOTIFY BlackClockTimeChanged)
        Q_PROPERTY(int WhiteMaterial READ WhiteMaterial WRITE setWhiteMaterial NOTIFY WhiteMaterialChanged)
        Q_PROPERTY(int BlackMaterial READ BlackMaterial WRITE setBlackMaterial NOTIFY BlackMaterialChanged)
        Q_PROPERTY(bool IsWhiteOnMove READ IsWhiteOnMove WRITE setIsWhiteOnMove NOTIFY IsWhiteOnMoveChanged)
        Q_PROPERTY(int MoveNumber READ MoveNumber WRITE setMoveNumber NOTIFY MoveNumberChanged)
        Q_PROPERTY(bool IsExamined READ IsExamined WRITE setIsExamined NOTIFY IsExaminedChanged)

    public:
        explicit FicsGameInfo(QObject *parent = nullptr);
        FicsGameInfo(const FicsGameInfo &other);
        FicsGameInfo &operator =(const FicsGameInfo &other);
        bool operator ==(const FicsGameInfo &other) const;

        int GameID() const;
        QString WhiteRating() const;
        QString BlackRating() const;
        QString WhiteName() const;
        QString BlackName() const;
        bool IsPrivate() const;
        QString GameCategory() const;
        bool IsRated() const;
        int TimeMinutes() const;
        int TimeIncrement() const;
        QString WhiteClockTime() const;
        QString BlackClockTime() const;
        int WhiteMaterial() const;
        int BlackMaterial() const;
        bool IsWhiteOnMove() const;
        int MoveNumber() const;
        bool IsExamined() const;

        QString LongGameCategory() const;

    signals:

        void GameIDChanged(int GameID);
        void WhiteRatingChanged(QString WhiteRating);
        void BlackRatingChanged(QString BlackRating);
        void WhiteNameChanged(QString WhiteName);
        void BlackNameChanged(QString BlackName);
        void IsPrivateChanged(bool IsPrivate);
        void GameCategoryChanged(QString GameCategory);
        void IsRatedChanged(bool IsRated);
        void TimeMinutesChanged(int TimeMinutes);
        void TimeIncrementChanged(int TimeIncrement);
        void WhiteClockTimeChanged(QString WhiteClockTime);
        void BlackClockTimeChanged(QString BlackClockTime);
        void WhiteMaterialChanged(int WhiteMaterial);
        void BlackMaterialChanged(int BlackMaterial);
        void IsWhiteOnMoveChanged(bool IsWhiteOnMove);
        void MoveNumberChanged(int MoveNumber);

        void IsExaminedChanged(bool IsExamined);

    public slots:
        void setGameID(int GameID);
        void setWhiteRating(QString WhiteRating);
        void setBlackRating(QString BlackRating);
        void setWhiteName(QString WhiteName);
        void setBlackName(QString BlackName);
        void setIsPrivate(bool IsPrivate);
        void setGameCategory(QString GameCategory);
        void setIsRated(bool IsRated);
        void setTimeMinutes(int TimeMinutes);
        void setTimeIncrement(int TimeIncrement);
        void setWhiteClockTime(QString WhiteClockTime);
        void setBlackClockTime(QString BlackClockTime);
        void setWhiteMaterial(int WhiteMaterial);
        void setBlackMaterial(int BlackMaterial);
        void setIsWhiteOnMove(bool IsWhiteOnMove);
        void setMoveNumber(int MoveNumber);

        void setIsExamined(bool IsExamined);

    private:
        int m_GameID;
        QString m_WhiteRating;
        QString m_BlackRating;
        QString m_WhiteName;
        QString m_BlackName;
        bool m_IsPrivate;
        QString m_GameCategory;
        bool m_IsRated;
        int m_TimeMinutes;
        int m_TimeIncrement;
        QString m_WhiteClockTime;
        QString m_BlackClockTime;
        int m_WhiteMaterial;
        int m_BlackMaterial;
        bool m_IsWhiteOnMove;
        int m_MoveNumber;

        void copyOther(const FicsGameInfo &other);
        bool m_IsExamined;
    };

#endif // FICSGAMEINFO_H


