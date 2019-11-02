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

#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QPalette>
#include <QColor>
#include <QRadioButton>
#include "configsettings.h"
#include "advancedconnectdialog.h"
#include "modifyconnectiondialog.h"

namespace Ui
{
class ConnectDialog;
}

class ConnectDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit ConnectDialog(QWidget *parent = nullptr);
        ~ConnectDialog();

        enum EnableVisibility { Guest, Connection, AdHoc};

        void LoadCredentials();
        int FindIndex(QString unique_key);
        void LoadIndex(int index);

    private:
        Ui::ConnectDialog *ui;
        ConfigSettings *options;

        QMap<QString, QMap<QString, QVariant>> conn_opts;
        QMap<QString, QMap<QString, QVariant>> cred_opts;
        //QMap<QString, QString> connection_selected;
        //QMap<QString, QString> connection_default;

        void ConnectTypeVisibility(bool checked);
        void SetEnableVisibility(EnableVisibility e);

    public slots:
        void ConnectionEditClicked();
        void CancelClicked();
        void ConnectClicked();
        void AdvancedClicked();
        void ConnectionIndexChanged(int index);


    };

#endif // CONNECTDIALOG_H
