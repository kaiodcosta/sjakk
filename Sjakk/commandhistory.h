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

#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include <QObject>
#include <QStringList>
#include <QDebug>

class CommandHistory : public QObject
    {
        Q_OBJECT

    private:
        QStringList history;
        int cursor;
        int history_maximum;

        void removeOverflow();

    public:
        explicit CommandHistory(QObject *parent = nullptr);
        void prepend(QString msg);
        void setMaximumHistory(int max_strings);

        QString history_current();
        QString history_previous();
        QString history_next();

    signals:

    public slots:

    };

#endif // COMMANDHISTORY_H
