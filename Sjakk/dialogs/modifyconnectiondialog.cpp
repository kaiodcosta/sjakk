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

#include "modifyconnectiondialog.h"
#include "ui_modifyconnectiondialog.h"

int ModifyConnectionDialog::FindIndex(QString unique_key)
    {
    return ui->comboBox_connection->findText(unique_key, Qt::MatchFlag::MatchExactly);
    }

void ModifyConnectionDialog::LoadCredentials()
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

ModifyConnectionDialog::ModifyConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyConnectionDialog)
    {
    ui->setupUi(this);
    options = ConfigSettings::Instance();
    port_validator = new QIntValidator(1, 65535, this);
    ui->lineEdit_serverport->setValidator(port_validator);
    connect(ui->pushButton_ok, &QPushButton::clicked, this, &ModifyConnectionDialog::OkClicked);
    connect(ui->pushButton_new, &QPushButton::clicked, this, &ModifyConnectionDialog::NewClicked);
    connect(ui->pushButton_save, &QPushButton::clicked, this, &ModifyConnectionDialog::SaveClicked);
    connect(ui->pushButton_edit, &QPushButton::clicked, this, &ModifyConnectionDialog::EditClicked);
    connect(ui->pushButton_remove, &QPushButton::clicked, this, &ModifyConnectionDialog::RemoveClicked);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &ModifyConnectionDialog::CancelClicked);
    connect(ui->comboBox_connection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ModifyConnectionDialog::ConnectionIndexChanged);
    connect(ui->lineEdit_user, &QLineEdit::textEdited, this, &ModifyConnectionDialog::UsernameEdited);
    connect(ui->lineEdit_serveraddress, &QLineEdit::textEdited, this, &ModifyConnectionDialog::ServerAddressEdited);
    cred_opts = options->get_structure("credentials");
    conn_opts = options->get_structure("connection");
    LoadCredentials();
    SetMode(ModifyMode::Browsing);
    }

ModifyConnectionDialog::~ModifyConnectionDialog()
    {
    delete ui;
    }

void ModifyConnectionDialog::SetMode(ModifyConnectionDialog::ModifyMode e)
    {
    current_mode = e;

    switch (e)
        {
        case Browsing:
            ui->lineEdit_user->setDisabled(true);
            ui->lineEdit_password->setDisabled(true);
            ui->lineEdit_serverport->setDisabled(true);
            ui->lineEdit_serveraddress->setDisabled(true);
            ui->pushButton_save->setDisabled(true);
            ui->pushButton_edit->setDisabled(false);
            ui->pushButton_new->setDisabled(false);
            ui->pushButton_remove->setDisabled(false);
            ui->pushButton_cancel->setDisabled(true);
            ui->comboBox_connection->setVisible(true);
            ui->comboBox_connection->setDisabled(false);

            if (ui->comboBox_connection->count() == 0)
                {
                ui->pushButton_edit->setDisabled(true);
                ui->pushButton_remove->setDisabled(true);
                }

            break;

        case New:
            ui->lineEdit_user->setDisabled(false);
            ui->lineEdit_password->setDisabled(false);
            ui->lineEdit_serverport->setDisabled(false);
            ui->lineEdit_serveraddress->setDisabled(false);
            ui->pushButton_save->setDisabled(false);
            ui->pushButton_edit->setDisabled(true);
            ui->pushButton_new->setDisabled(true);
            ui->pushButton_remove->setDisabled(true);
            ui->pushButton_cancel->setDisabled(false);
            ui->comboBox_connection->setVisible(false);
            ui->lineEdit_user->setText("");
            ui->lineEdit_password->setText("");
            ui->lineEdit_serverport->setText(conn_opts["default"]["port"].toString());
            ui->lineEdit_serveraddress->setText(conn_opts["default"]["address"].toString());
            ui->label_displayname->setText(QString("%1@%2").arg(ui->lineEdit_user->text()).arg(ui->lineEdit_serveraddress->text()));
            break;

        case Edit:
            ui->lineEdit_user->setDisabled(false);
            ui->lineEdit_password->setDisabled(false);
            ui->lineEdit_serverport->setDisabled(false);
            ui->lineEdit_serveraddress->setDisabled(false);
            ui->comboBox_connection->setDisabled(true);
            ui->pushButton_save->setDisabled(false);
            ui->pushButton_edit->setDisabled(true);
            ui->pushButton_new->setDisabled(true);
            ui->pushButton_remove->setDisabled(true);
            ui->pushButton_cancel->setDisabled(false);
            break;
        }
    }

void ModifyConnectionDialog::SaveClicked()
    {
    // save stuff
    int index = -1;

    if (current_mode == New)
        {
        QString server_address = ui->lineEdit_serveraddress->text().trimmed();
        QString server_port = ui->lineEdit_serverport->text().trimmed();
        QString user_name = ui->lineEdit_user->text().trimmed();
        QString password = ui->lineEdit_password->text();
        QString unique_key = QString("%1@%2").arg(user_name).arg(server_address);
        cred_opts[unique_key].insert("server", server_address);
        cred_opts[unique_key].insert("port", server_port);
        cred_opts[unique_key].insert("user", user_name);
        cred_opts[unique_key].insert("password", password);
        LoadCredentials();
        SetMode(Browsing);
        index = FindIndex(unique_key);
        }

    if (current_mode == Edit)
        {
        QString server_address = ui->lineEdit_serveraddress->text().trimmed();
        QString server_port = ui->lineEdit_serverport->text().trimmed();
        QString user_name = ui->lineEdit_user->text().trimmed();
        QString password = ui->lineEdit_password->text();
        QString unique_key = QString("%1@%2").arg(user_name).arg(server_address);
        QString old_key = ui->comboBox_connection->currentText();
        cred_opts.remove(old_key);
        cred_opts[unique_key].insert("server", server_address);
        cred_opts[unique_key].insert("port", server_port);
        cred_opts[unique_key].insert("user", user_name);
        cred_opts[unique_key].insert("password", password);
        LoadCredentials();
        SetMode(Browsing);
        index = FindIndex(unique_key);
        }

    if (index != -1)
        ui->comboBox_connection->setCurrentIndex(index);
    }

void ModifyConnectionDialog::NewClicked()
    {
    // hide combo box selection if possible
    SetMode(New);
    }

void ModifyConnectionDialog::EditClicked()
    {
    SetMode(Edit);
    }

void ModifyConnectionDialog::RemoveClicked()
    {
    // remove stuff
    SetMode(Browsing);
    QString key = ui->comboBox_connection->currentText();
    cred_opts.remove(key);
    LoadCredentials();
    }

void ModifyConnectionDialog::OkClicked()
    {
    options->clear_structure("credentials");
    options->set_structure("credentials", cred_opts);
    options->set_structure("connection", conn_opts);
    done(QDialog::DialogCode::Accepted);
    }

void ModifyConnectionDialog::CancelClicked()
    {
    // cancel current operation
    SetMode(Browsing);
    LoadIndex(ui->comboBox_connection->currentIndex());
    }

void ModifyConnectionDialog::LoadIndex(int index)
    {
    QString key = ui->comboBox_connection->itemText(index);
    ui->lineEdit_serveraddress->setText(cred_opts[key]["server"].toString());
    ui->lineEdit_serverport->setText(cred_opts[key]["port"].toString());
    ui->lineEdit_user->setText(cred_opts[key]["user"].toString());
    ui->lineEdit_password->setText(cred_opts[key]["password"].toString());
    conn_opts["selected"]["address"] = cred_opts[key]["server"];
    conn_opts["selected"]["port"] = cred_opts[key]["port"];
    conn_opts["selected"]["user"] = cred_opts[key]["user"];
    conn_opts["selected"]["password"] = cred_opts[key]["password"];
    ui->label_displayname->setText(key);
    }

void ModifyConnectionDialog::ConnectionIndexChanged(int index)
    {
    if (index == -1)
        return;

    LoadIndex(index);
    }

void ModifyConnectionDialog::UsernameEdited(const QString &text)
    {
    QString newkey = QString("%1@%2").arg(text).arg(ui->lineEdit_serveraddress->text());
    ui->label_displayname->setText(newkey);
    }

void ModifyConnectionDialog::ServerAddressEdited(const QString &text)
    {
    QString newkey = QString("%1@%2").arg(text).arg(ui->lineEdit_user->text());
    ui->label_displayname->setText(newkey);
    }
