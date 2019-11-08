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

#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

void PreferencesDialog::InitUiState()
    {
    ui->pushButton_apply->setDisabled(true);

    if (static_cast<QTextOption::WrapMode>(wgt_opts["console"]["wordwrap"].toInt()) == QTextOption::WrapMode::WordWrap)
        {
        ui->checkBox_wordwrap->setChecked(true);
        }
    else
        {
        ui->checkBox_wordwrap->setChecked(false);
        }

    for (int i = 0; i < ui->fontComboBox_console->count(); i++)
        {
        if (wgt_opts["console"]["font"] == ui->fontComboBox_console->itemText(i))
            {
            ui->fontComboBox_console->setCurrentIndex(i);
            break;
            }
        }

    ui->doubleSpinBox_pointsize->setValue(wgt_opts["console"]["pointsize"].toDouble());
    ui->label_prefslocation->setText(QString("Preferences Location: %1").arg(options->get_map("info").value("preferences_location").toString()));
    }

void PreferencesDialog::saveOptions()
    {
    wgt_opts["console"]["font"] = ui->fontComboBox_console->currentText();
    wgt_opts["console"]["pointsize"] = ui->doubleSpinBox_pointsize->value();
    wgt_opts["console"]["wordwrap"] = ui->checkBox_wordwrap->isChecked() ? QTextOption::WrapMode::WordWrap : QTextOption::WrapMode::NoWrap;
    options->set_structure("widgets", wgt_opts);
    }

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
    {
    ui->setupUi(this);
    options = ConfigSettings::Instance();
    wgt_opts = options->get_structure("widgets");
    InitUiState();
    connect(ui->fontComboBox_console, QOverload<int>::of(&QFontComboBox::currentIndexChanged), this, &PreferencesDialog::comboBoxOptionChanged);
    connect(ui->doubleSpinBox_pointsize, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &PreferencesDialog::spinBoxOptionChanged);
    connect(ui->checkBox_wordwrap, &QCheckBox::toggled, this, &PreferencesDialog::checkBoxOptionChanged);
    connect(ui->pushButton_ok, &QPushButton::clicked, this, &PreferencesDialog::OkClicked);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &PreferencesDialog::CancelClicked);
    connect(ui->pushButton_apply, &QPushButton::clicked, this, &PreferencesDialog::ApplyClicked);
    }

PreferencesDialog::~PreferencesDialog()
    {
    delete ui;
    }
void PreferencesDialog::OkClicked()
    {
    saveOptions();
    done(QDialog::DialogCode::Accepted);
    }
void PreferencesDialog::ApplyClicked()
    {
    saveOptions();
    ui->pushButton_apply->setDisabled(true);
    }
void PreferencesDialog::CancelClicked()
    {
    done(QDialog::DialogCode::Rejected);
    }

void PreferencesDialog::comboBoxOptionChanged(int index)
    {
    (void)index;
    ui->pushButton_apply->setDisabled(false);
    }

void PreferencesDialog::spinBoxOptionChanged(const QString &newvalue)
    {
    (void)newvalue;
    ui->pushButton_apply->setDisabled(false);
    }

void PreferencesDialog::checkBoxOptionChanged(bool checked)
    {
    (void)checked;
    ui->pushButton_apply->setDisabled(false);
    }

