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

#include "connectdialog.h"
#include "ui_connectdialog.h"

int ConnectDialog::FindIndex(QString unique_key)
    {
    return ui->comboBox_connection->findText(unique_key, Qt::MatchFlag::MatchExactly);
    }

void ConnectDialog::LoadCredentials()
    {
    ui->comboBox_connection->clear();

    foreach (QString cred_key, cred_opts.keys())
        ui->comboBox_connection->addItem(cred_key);

    QString selected_key = QString("%1@%2")
                           .arg(conn_opts["selected"]["user"].toString())
                           .arg(conn_opts["selected"]["address"].toString());

    if (cred_opts.contains(selected_key))
        {
        int index = FindIndex(selected_key);

        if (index != -1)
            ui->comboBox_connection->setCurrentIndex(index);
        }
    }

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
    {
    ui->setupUi(this);
    options = ConfigSettings::Instance();
    connect(ui->radioButton_adhoc, &QRadioButton::toggled, this, &ConnectDialog::ConnectTypeVisibility);
    connect(ui->radioButton_guest, &QRadioButton::toggled, this, &ConnectDialog::ConnectTypeVisibility);
    connect(ui->radioButton_connection, &QRadioButton::toggled, this, &ConnectDialog::ConnectTypeVisibility);
    connect(ui->pushButton_connectionEdit, &QPushButton::clicked, this, &ConnectDialog::ConnectionEditClicked);
    connect(ui->pushButton_advanced, &QPushButton::clicked, this, &ConnectDialog::AdvancedClicked);
    connect(ui->pushButton_connect, &QPushButton::clicked, this, &ConnectDialog::ConnectClicked);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &ConnectDialog::CancelClicked);
    connect(ui->comboBox_connection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ConnectDialog::ConnectionIndexChanged);
    cred_opts = options->get_structure("credentials");
    conn_opts = options->get_structure("connection");
    LoadCredentials();
    ui->radioButton_guest->setChecked(true);
    ConnectTypeVisibility(true);
    }

ConnectDialog::~ConnectDialog()
    {
    delete ui;
    }

void ConnectDialog::SetEnableVisibility(EnableVisibility e)
    {
    switch (e)
        {
        case EnableVisibility::Guest:
            ui->lineEdit_user->setEnabled(false);
            ui->lineEdit_password->setEnabled(false);
            ui->lineEdit_serverport->setEnabled(false);
            ui->lineEdit_serveraddress->setEnabled(false);
            ui->comboBox_connection->setEnabled(false);
            ui->pushButton_connectionEdit->setEnabled(false);
            ui->lineEdit_serverport->setText(conn_opts["default"]["port"].toString());
            ui->lineEdit_serveraddress->setText(conn_opts["default"]["address"].toString());
            break;

        case EnableVisibility::AdHoc:
            ui->lineEdit_user->setEnabled(true);
            ui->lineEdit_password->setEnabled(true);
            ui->lineEdit_serverport->setEnabled(true);
            ui->lineEdit_serveraddress->setEnabled(true);
            ui->comboBox_connection->setEnabled(false);
            ui->pushButton_connectionEdit->setEnabled(false);
            ui->lineEdit_serverport->setText(conn_opts["default"]["port"].toString());
            ui->lineEdit_serveraddress->setText(conn_opts["default"]["address"].toString());
            break;

        case EnableVisibility::Connection:
            ui->lineEdit_user->setEnabled(false);
            ui->lineEdit_password->setEnabled(false);
            ui->lineEdit_serverport->setEnabled(false);
            ui->lineEdit_serveraddress->setEnabled(false);
            ui->comboBox_connection->setEnabled(true);
            ui->pushButton_connectionEdit->setEnabled(true);
            break;
        }
    }

void ConnectDialog::ConnectTypeVisibility(bool checked)
    {
    if (checked)
        {
        if (ui->radioButton_guest->isChecked())
            SetEnableVisibility(EnableVisibility::Guest);

        if (ui->radioButton_adhoc->isChecked())
            SetEnableVisibility(EnableVisibility::AdHoc);

        if (ui->radioButton_connection->isChecked())
            SetEnableVisibility(EnableVisibility::Connection);
        }
    }


void ConnectDialog::ConnectionEditClicked()
    {
    QString current_key = ui->comboBox_connection->currentText();
    int current_index = ui->comboBox_connection->currentIndex();
    ModifyConnectionDialog connection_dialog(this);
    connection_dialog.exec();
    cred_opts = options->get_structure("credentials");
    conn_opts = options->get_structure("connection");
    LoadCredentials();
    QString selected_key = QString("%1@%2")
                           .arg(conn_opts["selected"]["user"].toString())
                           .arg(conn_opts["selected"]["address"].toString());
    int index = FindIndex(selected_key);

    if (index == -1)
        index = current_index - 1;

    ui->comboBox_connection->setCurrentIndex(index);
    }

void ConnectDialog::CancelClicked()
    {
    done(QDialog::DialogCode::Rejected);
    }

void ConnectDialog::ConnectClicked()
    {
    if (ui->radioButton_guest->isChecked())
        {
        conn_opts["selected"]["type"] = "guest";
        conn_opts["selected"]["user"] = "guest";
        }

    if (ui->radioButton_adhoc->isChecked() || ui->radioButton_connection->isChecked())
        {
        conn_opts["selected"]["type"] = "credentials";
        conn_opts["selected"]["address"] = ui->lineEdit_serveraddress->text();
        conn_opts["selected"]["port"] = ui->lineEdit_serverport->text();
        conn_opts["selected"]["user"] = ui->lineEdit_user->text();
        conn_opts["selected"]["password"] = ui->lineEdit_password->text();
        }

    options->set_structure("connection", conn_opts);
    done(QDialog::DialogCode::Accepted);
    }

void ConnectDialog::AdvancedClicked()
    {
    AdvancedConnectDialog advanced_dialog(this);
    int result = advanced_dialog.exec();

    if (result == QDialog::DialogCode::Accepted)
        {
        conn_opts = options->get_structure("connection");

        if (ui->radioButton_guest->isChecked())
            {
            ui->lineEdit_serverport->setText(conn_opts["default"]["port"].toString());
            ui->lineEdit_serveraddress->setText(conn_opts["default"]["address"].toString());
            }
        }
    }

void ConnectDialog::LoadIndex(int index)
    {
    QString key = ui->comboBox_connection->itemText(index);
    ui->lineEdit_serveraddress->setText(cred_opts[key]["address"].toString());
    ui->lineEdit_serverport->setText(cred_opts[key]["port"].toString());
    ui->lineEdit_user->setText(cred_opts[key]["user"].toString());
    ui->lineEdit_password->setText(cred_opts[key]["password"].toString());
    }

void ConnectDialog::ConnectionIndexChanged(int index)
    {
    if (index == -1)
        return;

    LoadIndex(index);
    }
