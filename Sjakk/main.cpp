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

#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QtDebug>
#include <QDateTime>
#include <QMessageBox>
#include "config.h"
#include "configsettings.h"
#include "sjakkwindow.h"


QString writable_config_file()
    {
    // Try our best to find an appropriate standard location for our options file
    QString config_file = QString("%1.ini").arg(MY_APPNAME);
    QStringList path_list = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);

    foreach (QString path, path_list)
        {
        qDebug() << "Config Path: " << path;
        QDir candidate_dir(path);

        if (!candidate_dir.exists())
            {
            continue;
            }

        bool self_writable = false;

        foreach (QString el, candidate_dir.entryList(QDir::Filter::Dirs | QDir::Filter::Writable))
            {
            if (el == ".")
                {
                self_writable = true;
                break;
                }
            }

        if (self_writable == false)
            {
            continue;
            }

        config_file = candidate_dir.absoluteFilePath(QString("%1.ini").arg(MY_APPNAME));
        }

    qDebug() << "Candidate: " << config_file;
    return config_file;
    }

int main(int argc, char *argv[])
    {
    QApplication::setOrganizationName(MY_ORGNAME);
    QApplication::setOrganizationDomain(MY_ORGDOMAIN);
    QApplication::setApplicationName(MY_APPNAME);
    ConfigSettings *options = ConfigSettings::Instance();
    QString file_name = writable_config_file();
    options->set_ini_path(file_name);
    QMap<QString, QVariant> info;
    info.insert("preferences_location", file_name);
    options->set_map("info", info);
    QMap<QString, QVariant> org_info;
    org_info.insert("application_name", MY_APPNAME);
    org_info.insert("organization_name", MY_ORGNAME);
    org_info.insert("organization_domain", MY_ORGDOMAIN);
    options->set_map("application", org_info);
    QApplication a(argc, argv);
    SjakkWindow w;
    w.show();
    int return_code = a.exec();
    return return_code;
    }
