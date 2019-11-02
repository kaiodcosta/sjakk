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

#ifndef CHESSCLOCK_H
#define CHESSCLOCK_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QDebug>

class ChessClock : public QLabel
    {
        Q_OBJECT
        Q_PROPERTY(int MilliSeconds READ MilliSeconds WRITE setMilliSeconds NOTIFY MilliSecondsChanged)

    public:
        ChessClock(QWidget *parent = nullptr);
        int MilliSeconds() const;

    public slots:
        void setSeconds(int Seconds);
        void setMilliSeconds(int MilliSeconds);

        void StartCountDown();
        void StopCountDown();
    signals:
        void MilliSecondsChanged(int MilliSeconds);

    private slots:
        void showTime();
        void timerTimeOut();

    private:
        int m_MilliSeconds;

        QTimer *m_Timer;
        QTime *m_RunningTime;

        QString defaultStyleSheet;

        void convertMSecsToTimeParts(int msecs, int &hr, int &mn, int &sc, int &ml);
    };

#endif // CHESSCLOCK_H
