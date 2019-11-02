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

#include "commandhistory.h"

CommandHistory::CommandHistory(QObject *parent) : QObject(parent)
    {
    history_maximum = 1000;
    cursor = -1;
    }

void CommandHistory::removeOverflow()
    {
    int overflow = history.size() - history_maximum;

    if (overflow >= 0)
        {
        while (overflow >= 0)
            {
            history.removeLast();
            overflow--;
            }

        if (cursor > history_maximum)
            cursor = history_maximum;
        }
    }

void CommandHistory::prepend(QString msg)
    {
    history.append(msg);
    //cursor++;
    removeOverflow();
    }

void CommandHistory::setMaximumHistory(int max_strings)
    {
    history_maximum = max_strings;
    removeOverflow();
    }

QString CommandHistory::history_current()
    {
    if (cursor == -1)
        return "";

    return history.at(cursor);
    }

QString CommandHistory::history_previous()
    {
    if ((cursor >= 0) && (cursor < history.size()))
        {
        qDebug() << "history_previous" << "cursor:" << cursor << "history size:" << history.size() << "max:" << history_maximum;
        return history.at(cursor--);
        }
    else
        return "";
    }

QString CommandHistory::history_next()
    {
    if ((cursor < history_maximum) && (cursor < (history.size() - 1)))
        {
        cursor++;
        qDebug() << "history_next() " << "cursor:" << cursor << "history size:" << history.size() << "max:" << history_maximum;
        return history.at(cursor);
        }
    else
        return "";
    }
