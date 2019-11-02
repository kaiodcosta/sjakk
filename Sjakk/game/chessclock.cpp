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

#include "chessclock.h"

ChessClock::ChessClock(QWidget *parent):
    QLabel(parent),
    m_Timer(new QTimer(this)),
    m_RunningTime(new QTime())
    {
    connect(m_Timer, &QTimer::timeout, this, &ChessClock::timerTimeOut);
    }

int ChessClock::MilliSeconds() const
    {
    return m_MilliSeconds;
    }

void ChessClock::StartCountDown()
    {
    defaultStyleSheet = this->styleSheet();
    this->setStyleSheet("QLabel { font-size: 14pt; background-color : lightgray; color : blue; font-weight : bold; }");
    m_RunningTime->start();
    m_Timer->start(1000);
    }

void ChessClock::StopCountDown()
    {
    this->setStyleSheet(defaultStyleSheet);
    this->setStyleSheet("QLabel { font-weight : bold; font-size: 14pt;}");
    m_Timer->stop();
    showTime();
    }

void ChessClock::setMilliSeconds(int MilliSeconds)
    {
    if (m_MilliSeconds == MilliSeconds)
        return;

    m_MilliSeconds = MilliSeconds;
    this->showTime();
    emit MilliSecondsChanged(m_MilliSeconds);
    }

void ChessClock::setSeconds(int Seconds)
    {
    this->setMilliSeconds(Seconds * 1000);
    }

void ChessClock::showTime()
    {
    int hours, minutes, seconds, milliseconds;
    convertMSecsToTimeParts(qAbs(m_MilliSeconds), hours, minutes, seconds, milliseconds);
    this->setText(QString("%1%2")
                  .arg(m_MilliSeconds < 0 ? "-" : "")
                  .arg(QTime(hours, minutes, seconds).toString("hh:mm:ss")));
    }

void ChessClock::timerTimeOut()
    {
    int elapsed = m_RunningTime->restart();
    this->setMilliSeconds(m_MilliSeconds - elapsed);
    }

void ChessClock::convertMSecsToTimeParts(int msecs, int &hr, int &mn, int &sc, int &ml)
    {
    hr = msecs / (1000 * 60 * 60);
    mn = (msecs - (hr * 1000 * 60 * 60)) / (1000 * 60);
    sc = (msecs - (mn * 1000 * 60) - (hr * 1000 * 60 * 60)) / 1000;
    ml = msecs - (sc * 1000) - (mn * 1000 * 60) - (hr * 1000 * 60 * 60);
    }
