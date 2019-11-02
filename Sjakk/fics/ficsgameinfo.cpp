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

#include "ficsgameinfo.h"
#include <QDebug>

FicsGameInfo::FicsGameInfo(QObject *parent) : QObject(parent)
    {
    this->m_GameID = -1;
    this->m_WhiteRating = "";
    this->m_WhiteName = "";
    this->m_BlackRating = "";
    this->m_BlackName = "";
    this->m_IsPrivate = false;
    this->m_GameCategory = "";
    this->m_IsRated = false;
    this->m_TimeMinutes = 0;
    this->m_TimeIncrement = 0;
    this->m_WhiteClockTime = "";
    this->m_BlackClockTime = "";
    this->m_WhiteMaterial = 0;
    this->m_BlackMaterial = 0;
    this->m_IsWhiteOnMove = false;
    this->m_MoveNumber = 0;
    this->m_IsExamined = false;
    }

FicsGameInfo::FicsGameInfo(const FicsGameInfo &other) : QObject()
    {
    copyOther(other);
    }

FicsGameInfo &FicsGameInfo::operator =(const FicsGameInfo &other)
    {
    copyOther(other);
    return *this;
    }

bool FicsGameInfo::operator ==(const FicsGameInfo &other) const
    {
    return m_GameID == other.m_GameID;
    }

int FicsGameInfo::GameID() const
    {
    return m_GameID;
    }

QString FicsGameInfo::WhiteRating() const
    {
    return m_WhiteRating;
    }

QString FicsGameInfo::BlackRating() const
    {
    return m_BlackRating;
    }

QString FicsGameInfo::WhiteName() const
    {
    return m_WhiteName;
    }

QString FicsGameInfo::BlackName() const
    {
    return m_BlackName;
    }

bool FicsGameInfo::IsPrivate() const
    {
    return m_IsPrivate;
    }

QString FicsGameInfo::GameCategory() const
    {
    return m_GameCategory;
    }

bool FicsGameInfo::IsRated() const
    {
    return m_IsRated;
    }

int FicsGameInfo::TimeMinutes() const
    {
    return m_TimeMinutes;
    }

int FicsGameInfo::TimeIncrement() const
    {
    return m_TimeIncrement;
    }

QString FicsGameInfo::WhiteClockTime() const
    {
    return m_WhiteClockTime;
    }

QString FicsGameInfo::BlackClockTime() const
    {
    return m_BlackClockTime;
    }

int FicsGameInfo::WhiteMaterial() const
    {
    return m_WhiteMaterial;
    }

int FicsGameInfo::BlackMaterial() const
    {
    return m_BlackMaterial;
    }

bool FicsGameInfo::IsWhiteOnMove() const
    {
    return m_IsWhiteOnMove;
    }

int FicsGameInfo::MoveNumber() const
    {
    return m_MoveNumber;
    }

bool FicsGameInfo::IsExamined() const
    {
    return m_IsExamined;
    }

QString FicsGameInfo::LongGameCategory() const
    {
    if (m_GameCategory.isEmpty())
        return "unknown";

    switch (m_GameCategory[0].toLatin1())
        {
        case 'b':
            return "blitz";

        case 's':
            return "standard";

        case 'B':
            return "bughouse";

        case 'n':
            return "non-standard";

        case 'l':
            return "lightning";

        case 'w':
            return "wild";

        case 'L':
            return "losers";

        case 'u':
            return "untimed";

        case 'x':
            return "atomic";

        case 'S':
            return "suicide";

        case 'e':
            return "examined";

        case 'z':
            return "crazyhouse";

        default:
            return "uknown";
        }
    }

void FicsGameInfo::setGameID(int GameID)
    {
    if (m_GameID == GameID)
        return;

    m_GameID = GameID;
    emit GameIDChanged(m_GameID);
    }

void FicsGameInfo::setWhiteRating(QString WhiteRating)
    {
    if (m_WhiteRating == WhiteRating)
        return;

    m_WhiteRating = WhiteRating;
    emit WhiteRatingChanged(m_WhiteRating);
    }

void FicsGameInfo::setBlackRating(QString BlackRating)
    {
    if (m_BlackRating == BlackRating)
        return;

    m_BlackRating = BlackRating;
    emit BlackRatingChanged(m_BlackRating);
    }

void FicsGameInfo::setWhiteName(QString WhiteName)
    {
    if (m_WhiteName == WhiteName)
        return;

    m_WhiteName = WhiteName;
    emit WhiteNameChanged(m_WhiteName);
    }

void FicsGameInfo::setBlackName(QString BlackName)
    {
    if (m_BlackName == BlackName)
        return;

    m_BlackName = BlackName;
    emit BlackNameChanged(m_BlackName);
    }

void FicsGameInfo::setIsPrivate(bool IsPrivate)
    {
    if (m_IsPrivate == IsPrivate)
        return;

    m_IsPrivate = IsPrivate;
    emit IsPrivateChanged(m_IsPrivate);
    }

void FicsGameInfo::setGameCategory(QString GameCategory)
    {
    if (m_GameCategory == GameCategory)
        return;

    m_GameCategory = GameCategory;
    emit GameCategoryChanged(m_GameCategory);
    }

void FicsGameInfo::setIsRated(bool IsRated)
    {
    if (m_IsRated == IsRated)
        return;

    m_IsRated = IsRated;
    emit IsRatedChanged(m_IsRated);
    }

void FicsGameInfo::setTimeMinutes(int TimeMinutes)
    {
    if (m_TimeMinutes == TimeMinutes)
        return;

    m_TimeMinutes = TimeMinutes;
    emit TimeMinutesChanged(m_TimeMinutes);
    }

void FicsGameInfo::setTimeIncrement(int TimeIncrement)
    {
    if (m_TimeIncrement == TimeIncrement)
        return;

    m_TimeIncrement = TimeIncrement;
    emit TimeIncrementChanged(m_TimeIncrement);
    }

void FicsGameInfo::setWhiteClockTime(QString WhiteClockTime)
    {
    if (m_WhiteClockTime == WhiteClockTime)
        return;

    m_WhiteClockTime = WhiteClockTime;
    emit WhiteClockTimeChanged(m_WhiteClockTime);
    }

void FicsGameInfo::setBlackClockTime(QString BlackClockTime)
    {
    if (m_BlackClockTime == BlackClockTime)
        return;

    m_BlackClockTime = BlackClockTime;
    emit BlackClockTimeChanged(m_BlackClockTime);
    }

void FicsGameInfo::setWhiteMaterial(int WhiteMaterial)
    {
    if (m_WhiteMaterial == WhiteMaterial)
        return;

    m_WhiteMaterial = WhiteMaterial;
    emit WhiteMaterialChanged(m_WhiteMaterial);
    }

void FicsGameInfo::setBlackMaterial(int BlackMaterial)
    {
    if (m_BlackMaterial == BlackMaterial)
        return;

    m_BlackMaterial = BlackMaterial;
    emit BlackMaterialChanged(m_BlackMaterial);
    }

void FicsGameInfo::setIsWhiteOnMove(bool IsWhiteOnMove)
    {
    if (m_IsWhiteOnMove == IsWhiteOnMove)
        return;

    m_IsWhiteOnMove = IsWhiteOnMove;
    emit IsWhiteOnMoveChanged(m_IsWhiteOnMove);
    }

void FicsGameInfo::setMoveNumber(int MoveNumber)
    {
    if (m_MoveNumber == MoveNumber)
        return;

    m_MoveNumber = MoveNumber;
    emit MoveNumberChanged(m_MoveNumber);
    }

void FicsGameInfo::setIsExamined(bool IsExamined)
    {
    if (m_IsExamined == IsExamined)
        return;

    m_IsExamined = IsExamined;
    emit IsExaminedChanged(m_IsExamined);
    }

void FicsGameInfo::copyOther(const FicsGameInfo &other)
    {
    this->m_GameID = other.m_GameID;
    this->m_WhiteRating = other.m_WhiteRating;
    this->m_WhiteName = other.m_WhiteName;
    this->m_BlackRating = other.m_BlackRating;
    this->m_BlackName = other.m_BlackName;
    this->m_IsPrivate = other.m_IsPrivate;
    this->m_GameCategory = other.m_GameCategory;
    this->m_IsRated = other.m_IsRated;
    this->m_TimeMinutes = other.m_TimeMinutes;
    this->m_TimeIncrement = other.m_TimeIncrement;
    this->m_WhiteClockTime = other.m_WhiteClockTime;
    this->m_BlackClockTime = other.m_BlackClockTime;
    this->m_WhiteMaterial = other.m_WhiteMaterial;
    this->m_BlackMaterial = other.m_BlackMaterial;
    this->m_IsWhiteOnMove = other.m_IsWhiteOnMove;
    this->m_MoveNumber = other.m_MoveNumber;
    this->m_IsExamined = other.m_IsExamined;
    }
