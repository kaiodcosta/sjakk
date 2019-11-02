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

#ifndef CONFIGSETTINGS_H
#define CONFIGSETTINGS_H

#include <QSettings>
#include <QVariant>
#include <QDebug>

class ConfigSettings
    {
    public:
        static ConfigSettings *Instance();

        bool contains(QString key);

        void clear_map(QString map_name);
        void clear_structure(QString struct_name);

        QList<QVariant> get_list(QString list_name);
        QMap<QString, QVariant> get_map(QString map_name);
        QMap<QString, QMap<QString, QVariant>> get_structure(QString struct_name);

        void set_ini_path(QString file_path);
        void set_list(QString list_name, QList<QVariant> list_obj);
        void set_map(QString map_name, QMap<QString, QVariant> map_obj);
        void set_structure(QString struct_name, QMap<QString, QMap<QString, QVariant>> struct_obj);

        void sync();


    private:
        ConfigSettings() {}
        ConfigSettings(ConfigSettings const &) {}
        ConfigSettings &operator=(ConfigSettings const &) {}
        static ConfigSettings *instance;

        QSettings *config_obj;

    };

#endif // CONFIGSETTINGS_H
