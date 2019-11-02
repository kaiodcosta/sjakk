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

#include "seekdialog.h"
#include "ui_seekdialog.h"

void SeekDialog::LoadSeekOptions()
    {
    ui->spinBox_time->setValue(seek_obj["default"]["time_min"].toInt());
    ui->spinBox_increment->setValue(seek_obj["default"]["time_inc"].toInt());

    foreach (int key, GameFlags::GameTypes.keys())
        ui->comboBox_gametype->addItem(GameFlags::GameTypes[key], key);

    int index = ui->comboBox_gametype->findData(seek_obj["default"]["game_type"].toInt());
    ui->comboBox_gametype->setCurrentIndex(index == -1 ? 0 : index);
    ui->spinBox_minrating->setValue(seek_obj["default"]["min_rating"].toInt());
    ui->spinBox_maxrating->setValue(seek_obj["default"]["max_rating"].toInt());
    ui->checkBox_rated->setChecked(seek_obj["default"]["rated"].toBool());
    ui->checkBox_manual->setChecked(seek_obj["default"]["manual"].toBool());
    ui->checkBox_formula->setChecked(seek_obj["default"]["formula"].toBool());

    if (seek_obj["default"]["color"] == "")
        ui->radioButton_automatic->setChecked(true);

    if (seek_obj["default"]["color"] == "w")
        ui->radioButton_white->setChecked(true);

    if (seek_obj["default"]["color"] == "b")
        ui->radioButton_black->setChecked(true);
    }

SeekDialog::SeekDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekDialog)
    {
    ui->setupUi(this);
    options = ConfigSettings::Instance();
    seek_obj = options->get_structure("seek");
    connect(ui->pushButton_ok, &QPushButton::clicked, this, &SeekDialog::OkClicked);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &SeekDialog::CancelClicked);
    LoadSeekOptions();
    }

SeekDialog::~SeekDialog()
    {
    delete ui;
    }

QByteArray SeekDialog::getSeekRequest()
    {
    QByteArray request;
    request += QString("seek %1%2%3%4%5%6%7%8")
               .arg(ui->spinBox_time->text() + " ")
               .arg(ui->spinBox_increment->text() + " ")
               .arg(ui->checkBox_rated->isChecked() ? "rated" : "unrated")
               .arg(getColorChoice() == "" ? "" : " " + getColorChoice())
               .arg(getGameType() == "" ? "" : " " + getGameType())
               .arg(ui->checkBox_manual->isChecked() ? " m" : "")
               .arg(ui->checkBox_formula->isChecked() ? " f" : "")
               .arg(getRatingRange() == "" ? "" : " " + getRatingRange());
    return request;
    }

QString SeekDialog::getGameType()
    {
    switch (ui->comboBox_gametype->currentData().toInt())
        {
        case GameFlags::GameType::FischerRandom:
            return "wild fr";

        default:
            return "";
        }
    }

QString SeekDialog::getRatingRange()
    {
    if ((ui->spinBox_minrating->value() == 0) && (ui->spinBox_maxrating->value() == 9999))
        return "";
    else
        return QString("%1-%2")
               .arg(ui->spinBox_minrating->value())
               .arg(ui->spinBox_maxrating->value());
    }

QString SeekDialog::getColorChoice()
    {
    QString choice = "";

    if (ui->radioButton_black->isChecked())
        choice = "b";

    if (ui->radioButton_white->isChecked())
        choice = "w";

    return choice;
    }

void SeekDialog::UpdateSeekOptions()
    {
    seek_obj["default"]["game_type"] = ui->comboBox_gametype->currentData().toInt();
    seek_obj["default"]["time_min"] = ui->spinBox_time->value();
    seek_obj["default"]["time_inc"] = ui->spinBox_increment->value();
    seek_obj["default"]["min_rating"] = ui->spinBox_minrating->value();
    seek_obj["default"]["max_rating"] = ui->spinBox_maxrating->value();
    seek_obj["default"]["rated"] = ui->checkBox_rated->isChecked();
    seek_obj["default"]["manual"] = ui->checkBox_manual->isChecked();
    seek_obj["default"]["formula"] = ui->checkBox_formula->isChecked();
    seek_obj["default"]["color"] = getColorChoice();
    options->set_structure("seek", seek_obj);
    }

void SeekDialog::OkClicked()
    {
    UpdateSeekOptions();
    done(QDialog::DialogCode::Accepted);
    }

void SeekDialog::CancelClicked()
    {
    done(QDialog::DialogCode::Rejected);
    }
