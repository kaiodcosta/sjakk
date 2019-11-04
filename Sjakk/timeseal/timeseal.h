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

#ifndef TIMESEAL_H
#define TIMESEAL_H

#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QSysInfo>


class Timeseal : public QObject
    {
        Q_OBJECT
    private:
        QByteArray timeseal_key = "Timestamp (FICS) v1.0 - programmed by Henrik Gram.";
        QByteArray version = "QtTimeSeal 0.0.1";
        QByteArray ping = QByteArray("[G]\0", 4);
        QByteArray pong = "\x02\x39";

        void xor_swap(QByteArray &buffer, int a, int b);

    public:
        Timeseal(QObject *parent = nullptr);

        QByteArray hello();
        QByteArray stamp(QByteArray &buffer);
        void process(QByteArray &buffer);

    signals:
        void ping_echo(QByteArray ack);

    public slots:

    };

#endif // TIMESEAL_H
