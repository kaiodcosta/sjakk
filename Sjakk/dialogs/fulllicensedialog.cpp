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

#include "fulllicensedialog.h"
#include "ui_fulllicensedialog.h"

FullLicenseDialog::FullLicenseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FullLicenseDialog)
    {
    ui->setupUi(this);
    connect(ui->pushButton_ok, &QPushButton::clicked, this, &FullLicenseDialog::OkClicked);
    QFile f(":/media/documents/COPYING");
    QString mText = "";

    if (!f.open(QFile::ReadOnly | QFile::Text))
        qDebug() << "could not open file for read";
    else
        {
        QTextStream in(&f);
        mText = in.readAll();
        }

    f.close();
    ui->textBrowser_license->setText(mText);
    }

FullLicenseDialog::~FullLicenseDialog()
    {
    delete ui;
    }

void FullLicenseDialog::OkClicked()
    {
    done(QDialog::DialogCode::Accepted);
    }
