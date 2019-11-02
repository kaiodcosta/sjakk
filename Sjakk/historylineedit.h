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

#ifndef HISTORYLINEEDIT_H
#define HISTORYLINEEDIT_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include "commandhistory.h"

class HistoryLineEdit : public QLineEdit
    {
        Q_OBJECT
    private:
        CommandHistory command_history;

    public:
        explicit HistoryLineEdit(QWidget *parent = nullptr);

    signals:
        void historyNext(QString history_text);
        void historyPrevious(QString history_text);

    public slots:
        void addToHistory();

        // QWidget interface
    protected:
        void keyPressEvent(QKeyEvent *event) override;
    };

#endif // HISTORYLINEEDIT_H
