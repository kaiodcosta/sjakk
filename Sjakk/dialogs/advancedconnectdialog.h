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

#ifndef ADVANCEDCONNECTDIALOG_H
#define ADVANCEDCONNECTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QMap>
#include <QVariant>
#include "../configsettings.h"

namespace Ui
{
class AdvancedConnectDialog;
}

class AdvancedConnectDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit AdvancedConnectDialog(QWidget *parent = nullptr);
        ~AdvancedConnectDialog();

    private:
        Ui::AdvancedConnectDialog *ui;
        ConfigSettings *options;

        QMap<QString, QMap<QString, QVariant>> conn_opts;

    public slots:
        void SaveClicked();
        void CancelClicked();
    };

#endif // ADVANCEDCONNECTDIALOG_H
