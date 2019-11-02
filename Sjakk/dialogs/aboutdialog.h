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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include "fulllicensedialog.h"
#include "../config.h"

namespace Ui
{
class AboutDialog;
}

class AboutDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit AboutDialog(QWidget *parent = nullptr);
        ~AboutDialog();

    private:
        Ui::AboutDialog *ui;
        QString read_license_notice();
        QString read_copyright();

    public slots:
        void OkClicked();
        void FullLicenseClicked();
    };

#endif // ABOUTDIALOG_H
