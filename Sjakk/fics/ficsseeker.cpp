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

#include "ficsseeker.h"

FicsSeeker::FicsSeeker(QObject *parent) : QObject(parent)
    {
    this->m_seekerIndex = 0;
    this->m_seekerFromName = "";
    this->m_seekerTitles = QList<QString>();
    this->m_seekerRating = 0;
    this->m_seekerRatingType = RatingType::Established;
    this->m_seekerTimeControl = 0;
    this->m_seekerTimeIncrement = 0;
    this->m_seekerIsRated = false;
    this->m_seekerGameType = "";
    this->m_seekerColorRequest = WantColor::Any;
    this->m_seekerRatingMax = 0;
    this->m_seekerRatingMin = 0;
    this->m_seekerStartAutomatic = false;
    this->m_seekerFormulaChecked = false;
    }

FicsSeeker::FicsSeeker(const FicsSeeker &other) : QObject()
    {
    copyOther(other);
    }

FicsSeeker &FicsSeeker::operator =(const FicsSeeker &other)
    {
    copyOther(other);
    return *this;
    }

bool FicsSeeker::operator ==(const FicsSeeker &other) const
    {
    return m_seekerIndex == other.m_seekerIndex;
    }

void FicsSeeker::copyOther(const FicsSeeker &other)
    {
    this->m_seekerIndex = other.m_seekerIndex;
    this->m_seekerFromName = other.m_seekerFromName;
    this->m_seekerTitles = QList<QString>(other.m_seekerTitles);
    this->m_seekerRating = other.m_seekerRating;
    this->m_seekerRatingType = other.m_seekerRatingType;
    this->m_seekerTimeControl = other.m_seekerTimeControl;
    this->m_seekerTimeIncrement = other.m_seekerTimeIncrement;
    this->m_seekerIsRated = other.m_seekerIsRated;
    this->m_seekerGameType = other.m_seekerGameType;
    this->m_seekerColorRequest = other.m_seekerColorRequest;
    this->m_seekerRatingMax = other.m_seekerRatingMax;
    this->m_seekerRatingMin = other.m_seekerRatingMin;
    this->m_seekerStartAutomatic = other.m_seekerStartAutomatic;
    this->m_seekerFormulaChecked = other.m_seekerFormulaChecked;
    }

int FicsSeeker::seekerIndex() const
    {
    return m_seekerIndex;
    }

QString FicsSeeker::seekerFromName() const
    {
    return m_seekerFromName;
    }

QList<QString> FicsSeeker::seekerTitles() const
    {
    return m_seekerTitles;
    }

int FicsSeeker::seekerRating() const
    {
    return m_seekerRating;
    }

FicsSeeker::RatingType FicsSeeker::seekerRatingType() const
    {
    return m_seekerRatingType;
    }

int FicsSeeker::seekerTimeControl() const
    {
    return m_seekerTimeControl;
    }

int FicsSeeker::seekerTimeIncrement() const
    {
    return m_seekerTimeIncrement;
    }

bool FicsSeeker::seekerIsRated() const
    {
    return m_seekerIsRated;
    }

QString FicsSeeker::seekerGameType() const
    {
    return m_seekerGameType;
    }

FicsSeeker::WantColor FicsSeeker::seekerColorRequest() const
    {
    return m_seekerColorRequest;
    }

int FicsSeeker::seekerRatingMin() const
    {
    return m_seekerRatingMin;
    }

int FicsSeeker::seekerRatingMax() const
    {
    return m_seekerRatingMax;
    }

bool FicsSeeker::seekerStartAutomatic() const
    {
    return m_seekerStartAutomatic;
    }

bool FicsSeeker::seekerFormulaChecked() const
    {
    return m_seekerFormulaChecked;
    }

void FicsSeeker::setSeekerIndex(int seekerIndex)
    {
    m_seekerIndex = seekerIndex;
    }

void FicsSeeker::setSeekerFromName(QString seekerFromName)
    {
    m_seekerFromName = seekerFromName;
    }

void FicsSeeker::setSeekerTitles(QList<QString> seekerTitles)
    {
    m_seekerTitles = seekerTitles;
    }

void FicsSeeker::setSeekerTitles(QString hexvalue)
    {
    QList<QString> tits;
    bool ok;
    int titlevalue = hexvalue.toInt(&ok, 16);

    if ((titlevalue & 0x1) == 0x1)
        tits.append("unregistered");

    if ((titlevalue & 0x2) == 0x2)
        tits.append("computer");

    if ((titlevalue & 0x4) == 0x4)
        tits.append("GM");

    if ((titlevalue & 0x8) == 0x8)
        tits.append("IM");

    if ((titlevalue & 0x10) == 0x10)
        tits.append("FM");

    if ((titlevalue & 0x20) == 0x20)
        tits.append("WGM");

    if ((titlevalue & 0x40) == 0x40)
        tits.append("WIM");

    if ((titlevalue & 0x80) == 0x80)
        tits.append("WFM");

    this->setSeekerTitles(tits);
    }

void FicsSeeker::setSeekerRating(int seekerRating)
    {
    m_seekerRating = seekerRating;
    }

void FicsSeeker::setSeekerRatingType(FicsSeeker::RatingType seekerRatingType)
    {
    m_seekerRatingType = seekerRatingType;
    }

void FicsSeeker::setSeekerRatingType(QString ratingtype)
    {
    RatingType rt;
    rt = RatingType::Established;

    if (ratingtype == "E")
        rt = RatingType::Estimated;

    if (ratingtype == "P")
        rt = RatingType::Provisional;

    this->setSeekerRatingType(rt);
    }

void FicsSeeker::setSeekerTimeControl(int seekerTimeControl)
    {
    m_seekerTimeControl = seekerTimeControl;
    }

void FicsSeeker::setSeekerTimeIncrement(int seekerTimeIncrement)
    {
    m_seekerTimeIncrement = seekerTimeIncrement;
    }

void FicsSeeker::setSeekerIsRated(bool seekerIsRated)
    {
    m_seekerIsRated = seekerIsRated;
    }

void FicsSeeker::setSeekerGameType(QString seekerGameType)
    {
    m_seekerGameType = seekerGameType;
    }

void FicsSeeker::setSeekerColorRequest(FicsSeeker::WantColor seekerColorRequest)
    {
    m_seekerColorRequest = seekerColorRequest;
    }

void FicsSeeker::setSeekerColorRequest(QString colorrequest)
    {
    WantColor wc;
    wc = WantColor::Any;

    if (colorrequest == "W")
        wc = WantColor::White;

    if (colorrequest == "B")
        wc = WantColor::Black;

    this->setSeekerColorRequest(wc);
    }

void FicsSeeker::setSeekerRatingMin(int seekerRatingMin)
    {
    m_seekerRatingMin = seekerRatingMin;
    }

void FicsSeeker::setSeekerRatingMax(int seekerRatingMax)
    {
    m_seekerRatingMax = seekerRatingMax;
    }

void FicsSeeker::setSeekerStartAutomatic(bool seekerStartAutomatic)
    {
    m_seekerStartAutomatic = seekerStartAutomatic;
    }

void FicsSeeker::setSeekerFormulaChecked(bool seekerFormulaChecked)
    {
    m_seekerFormulaChecked = seekerFormulaChecked;
    }
