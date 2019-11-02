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

#ifndef MODIFYCONNECTIONDIALOG_H
#define MODIFYCONNECTIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QValidator>
#include <QIntValidator>
#include <QRegularExpression>
#include "../configsettings.h"

namespace Ui
{
class ModifyConnectionDialog;
}

class ModifyConnectionDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit ModifyConnectionDialog(QWidget *parent = nullptr);
        ~ModifyConnectionDialog();



    private:
        Ui::ModifyConnectionDialog *ui;
        ConfigSettings *options;

        QIntValidator *port_validator;

        QMap<QString, QMap<QString, QVariant>> cred_opts;
        QMap<QString, QMap<QString, QVariant>> conn_opts;

        enum ModifyMode {New, Edit, Browsing};

        ModifyMode current_mode;

        void SetMode(ModifyMode e);
        void LoadCredentials();
        void LoadIndex(int index);
        int FindIndex(QString unique_key);

    public slots:
        void SaveClicked();
        void NewClicked();
        void EditClicked();
        void RemoveClicked();
        void OkClicked();
        void CancelClicked();
        void ConnectionIndexChanged(int index);
        void UsernameEdited(const QString &text);
        void ServerAddressEdited(const QString &text);
    };

#endif // MODIFYCONNECTIONDIALOG_H
