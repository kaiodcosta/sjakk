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

#include "historylineedit.h"

HistoryLineEdit::HistoryLineEdit(QWidget *parent) : QLineEdit(parent)
    {
    connect(this,  &QLineEdit::returnPressed, this, &HistoryLineEdit::addToHistory);
    }

void HistoryLineEdit::addToHistory()
    {
    command_history.prepend(text());
    }

void HistoryLineEdit::keyPressEvent(QKeyEvent *event)
    {
    int key;
    key = event->key();

    switch (key)
        {
        case Qt::Key::Key_Up:
            emit historyNext(command_history.history_next());
            break;

        case Qt::Key::Key_Down:
            emit historyPrevious(command_history.history_previous());
            break;

        default:
            QLineEdit::keyPressEvent(event);
        }
    }
