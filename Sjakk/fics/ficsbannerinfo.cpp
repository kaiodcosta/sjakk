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

#include "ficsbannerinfo.h"

FicsBannerInfo::FicsBannerInfo(QObject *parent) : QObject(parent)
    {
    this->m_BannerDescription = "";
    this->m_BannerResult = "";
    this->m_BannerTitle = "";
    this->m_GameID = -1;
    }

FicsBannerInfo::FicsBannerInfo(const FicsBannerInfo &other) : QObject()
    {
    copyOther(other);
    }

FicsBannerInfo &FicsBannerInfo::operator =(const FicsBannerInfo &other)
    {
    copyOther(other);
    return *this;
    }

bool FicsBannerInfo::operator ==(const FicsBannerInfo &other) const
    {
    return m_GameID == other.m_GameID;
    }

int FicsBannerInfo::GameID() const
    {
    return m_GameID;
    }

QString FicsBannerInfo::BannerTitle() const
    {
    return m_BannerTitle;
    }

QString FicsBannerInfo::BannerDescription() const
    {
    return m_BannerDescription;
    }

QString FicsBannerInfo::BannerResult() const
    {
    return m_BannerResult;
    }

void FicsBannerInfo::setGameID(int GameID)
    {
    if (m_GameID == GameID)
        return;

    m_GameID = GameID;
    emit GameIDChanged(m_GameID);
    }

void FicsBannerInfo::setBannerTitle(QString BannerTitle)
    {
    if (m_BannerTitle == BannerTitle)
        return;

    m_BannerTitle = BannerTitle;
    emit BannerTitleChanged(m_BannerTitle);
    }

void FicsBannerInfo::setBannerDescription(QString BannerDescription)
    {
    if (m_BannerDescription == BannerDescription)
        return;

    m_BannerDescription = BannerDescription;
    emit BannerDescriptionChanged(m_BannerDescription);
    }

void FicsBannerInfo::setBannerResult(QString BannerResult)
    {
    if (m_BannerResult == BannerResult)
        return;

    m_BannerResult = BannerResult;
    emit BannerResultChanged(m_BannerResult);
    }

void FicsBannerInfo::copyOther(const FicsBannerInfo &other)
    {
    this->m_BannerDescription = other.m_BannerDescription;
    this->m_BannerResult = other.m_BannerResult;
    this->m_BannerTitle = other.m_BannerTitle;
    this->m_GameID = other.m_GameID;
    }
