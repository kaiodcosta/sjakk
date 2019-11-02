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

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
    {
    ui->setupUi(this);
    connect(ui->pushButton_ok, &QPushButton::clicked, this, &AboutDialog::OkClicked);
    connect(ui->pushButton_license, &QPushButton::clicked, this, &AboutDialog::FullLicenseClicked);
    ui->label_appname->setText(QString("%1 %2 version %3.%4.%5")
                               .arg(MY_APPNAME)
                               .arg(MY_VERSIONYEAR)
                               .arg(MY_VERSIONMAJOR)
                               .arg(MY_VERSIONMINOR)
                               .arg(MY_VERSIONBUILD));
    ui->textBrowser_notice->setText(read_license_notice());
    ui->label_copyright->setText(read_copyright());
    }

AboutDialog::~AboutDialog()
    {
    delete ui;
    }

QString AboutDialog::read_license_notice()
    {
    QFile f(":/media/documents/license-notice.txt");

    if (!f.open(QFile::ReadOnly | QFile::Text))
        {
        qDebug() << "could not open file for read";
        return "";
        }

    QTextStream in(&f);
    QString mText = in.readAll();
    f.close();
    return mText;
    }

QString AboutDialog::read_copyright()
    {
    QFile f(":/media/documents/copyright.txt");

    if (!f.open(QFile::ReadOnly | QFile::Text))
        {
        qDebug() << "could not open file for read";
        return "";
        }

    QTextStream in(&f);
    QString mText = in.readAll();
    f.close();
    return mText;
    }

void AboutDialog::OkClicked()
    {
    done(QDialog::DialogCode::Accepted);
    }

void AboutDialog::FullLicenseClicked()
    {
    FullLicenseDialog fldlg;
    fldlg.exec();
    }
