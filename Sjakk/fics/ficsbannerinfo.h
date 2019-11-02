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

#ifndef FICSBANNERINFO_H
#define FICSBANNERINFO_H

#include <QObject>

class FicsBannerInfo : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(int GameID READ GameID WRITE setGameID NOTIFY GameIDChanged)
        Q_PROPERTY(QString BannerTitle READ BannerTitle WRITE setBannerTitle NOTIFY BannerTitleChanged)
        Q_PROPERTY(QString BannerDescription READ BannerDescription WRITE setBannerDescription NOTIFY BannerDescriptionChanged)
        Q_PROPERTY(QString BannerResult READ BannerResult WRITE setBannerResult NOTIFY BannerResultChanged)

    public:
        explicit FicsBannerInfo(QObject *parent = nullptr);
        FicsBannerInfo(const FicsBannerInfo &other);
        FicsBannerInfo &operator =(const FicsBannerInfo &other);
        bool operator ==(const FicsBannerInfo &other) const;

        int GameID() const;
        QString BannerTitle() const;
        QString BannerDescription() const;
        QString BannerResult() const;

    signals:
        void GameIDChanged(int GameID);
        void BannerTitleChanged(QString BannerTitle);
        void BannerDescriptionChanged(QString BannerDescription);
        void BannerResultChanged(QString BannerResult);

    public slots:
        void setGameID(int GameID);
        void setBannerTitle(QString BannerTitle);
        void setBannerDescription(QString BannerDescription);
        void setBannerResult(QString BannerResult);

    private:
        int m_GameID;
        QString m_BannerTitle;
        QString m_BannerDescription;
        QString m_BannerResult;

        void copyOther(const FicsBannerInfo &other);

    };

#endif // FICSBANNERINFO_H
