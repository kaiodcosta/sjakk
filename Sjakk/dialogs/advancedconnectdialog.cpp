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

#include "advancedconnectdialog.h"
#include "ui_advancedconnectdialog.h"

AdvancedConnectDialog::AdvancedConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedConnectDialog)
    {
    ui->setupUi(this);
    options = ConfigSettings::Instance();
    connect(ui->pushButton_save, &QPushButton::clicked, this, &AdvancedConnectDialog::SaveClicked);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &AdvancedConnectDialog::CancelClicked);
    conn_opts = options->get_structure("connection");
    ui->checkBox_timeseal->setChecked(conn_opts["default"]["timeseal"].toBool());
    ui->lineEdit_serveraddress->setText(conn_opts["default"]["address"].toString());
    ui->lineEdit_serverport->setText(conn_opts["default"]["port"].toString());
    }

AdvancedConnectDialog::~AdvancedConnectDialog()
    {
    delete ui;
    }

void AdvancedConnectDialog::SaveClicked()
    {
    conn_opts["default"]["timeseal"] = ui->checkBox_timeseal->isChecked();
    conn_opts["default"]["port"] = ui->lineEdit_serverport->text().toInt();
    conn_opts["default"]["address"] = ui->lineEdit_serveraddress->text();
    options->set_structure("connection", conn_opts);
    done(QDialog::DialogCode::Accepted);
    }

void AdvancedConnectDialog::CancelClicked()
    {
    done(QDialog::DialogCode::Rejected);
    }
