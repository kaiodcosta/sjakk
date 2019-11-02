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

#ifndef FICSSEEKER_H
#define FICSSEEKER_H

#include <QObject>

class FicsSeeker : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(int seekerIndex READ seekerIndex WRITE setSeekerIndex)
        Q_PROPERTY(QString seekerFromName READ seekerFromName WRITE setSeekerFromName)
        Q_PROPERTY(QList<QString> seekerTitles READ seekerTitles WRITE setSeekerTitles)
        Q_PROPERTY(int seekerRating READ seekerRating WRITE setSeekerRating)
        Q_PROPERTY(RatingType seekerRatingType READ seekerRatingType WRITE setSeekerRatingType)
        Q_PROPERTY(int seekerTimeControl READ seekerTimeControl WRITE setSeekerTimeControl)
        Q_PROPERTY(int seekerTimeIncrement READ seekerTimeIncrement WRITE setSeekerTimeIncrement)
        Q_PROPERTY(bool seekerIsRated READ seekerIsRated WRITE setSeekerIsRated)
        Q_PROPERTY(QString seekerGameType READ seekerGameType WRITE setSeekerGameType)
        Q_PROPERTY(WantColor seekerColorRequest READ seekerColorRequest WRITE setSeekerColorRequest)
        Q_PROPERTY(int seekerRatingMin READ seekerRatingMin WRITE setSeekerRatingMin)
        Q_PROPERTY(int seekerRatingMax READ seekerRatingMax WRITE setSeekerRatingMax)
        Q_PROPERTY(bool seekerStartAutomatic READ seekerStartAutomatic WRITE setSeekerStartAutomatic)
        Q_PROPERTY(bool seekerFormulaChecked READ seekerFormulaChecked WRITE setSeekerFormulaChecked)

    public:
        explicit FicsSeeker(QObject *parent = nullptr);
        FicsSeeker(const FicsSeeker &other);

        FicsSeeker &operator =(const FicsSeeker &other);
        bool operator ==(const FicsSeeker &other) const;

        enum WantColor { White, Black, Any };
        enum RatingType { Established, Estimated, Provisional };

        int seekerIndex() const;
        QString seekerFromName() const;
        QList<QString> seekerTitles() const;
        int seekerRating() const;
        RatingType seekerRatingType() const;
        int seekerTimeControl() const;
        int seekerTimeIncrement() const;
        bool seekerIsRated() const;
        QString seekerGameType() const;
        WantColor seekerColorRequest() const;
        int seekerRatingMin() const;
        int seekerRatingMax() const;
        bool seekerStartAutomatic() const;
        bool seekerFormulaChecked() const;

    signals:

    public slots:

        void setSeekerIndex(int seekerIndex);
        void setSeekerFromName(QString seekerFromName);
        void setSeekerTitles(QList<QString> seekerTitles);
        void setSeekerTitles(QString hexvalue);
        void setSeekerRating(int seekerRating);
        void setSeekerRatingType(RatingType seekerRatingType);
        void setSeekerRatingType(QString ratingtype);
        void setSeekerTimeControl(int seekerTimeControl);
        void setSeekerTimeIncrement(int seekerTimeIncrement);
        void setSeekerIsRated(bool seekerIsRated);
        void setSeekerGameType(QString seekerGameType);
        void setSeekerColorRequest(WantColor seekerColorRequest);
        void setSeekerColorRequest(QString colorrequest);
        void setSeekerRatingMin(int seekerRatingMin);
        void setSeekerRatingMax(int seekerRatingMax);
        void setSeekerStartAutomatic(bool seekerStartAutomatic);
        void setSeekerFormulaChecked(bool seekerFormulaChecked);

    private:

        int m_seekerIndex;
        QString m_seekerFromName;
        QList<QString> m_seekerTitles;
        int m_seekerRating;
        RatingType m_seekerRatingType;
        int m_seekerTimeControl;
        int m_seekerTimeIncrement;
        bool m_seekerIsRated;
        QString m_seekerGameType;
        WantColor m_seekerColorRequest;
        int m_seekerRatingMin;
        int m_seekerRatingMax;
        bool m_seekerStartAutomatic;
        bool m_seekerFormulaChecked;

        void copyOther(const FicsSeeker &other);

    };

#endif // FICSSEEKER_H
