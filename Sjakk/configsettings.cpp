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

#include "configsettings.h"

ConfigSettings *ConfigSettings::instance = nullptr;

QMap<QString, QVariant> ConfigSettings::get_map(QString map_name)
    {
    config_obj->beginGroup(map_name);
    QMap<QString, QVariant> opts;

    foreach (QString key, config_obj->childKeys())
        {
        opts.insert(key, config_obj->value(key));
        }

    config_obj->endGroup();
    return opts;
    }

QMap<QString, QMap<QString, QVariant> > ConfigSettings::get_structure(QString struct_name)
    {
    QMap<QString, QMap<QString, QVariant>> struct_obj;
    config_obj->beginGroup(struct_name);

    foreach (QString struct_key, config_obj->childGroups())
        {
        QMap<QString, QVariant> map_obj;
        config_obj->beginGroup(struct_key);

        foreach (QString map_key, config_obj->childKeys())
            {
            map_obj.insert(map_key, config_obj->value(map_key));
            }

        config_obj->endGroup();
        struct_obj.insert(struct_key, map_obj);
        }

    config_obj->endGroup();
    return struct_obj;
    }

void ConfigSettings::set_ini_path(QString file_path)
    {
    config_obj = new QSettings(file_path, QSettings::Format::IniFormat);
    }

ConfigSettings *ConfigSettings::Instance()
    {
    if (instance == nullptr)
        {
        instance = new ConfigSettings;
        }

    return instance;
    }

bool ConfigSettings::contains_map(QString map_name)
    {
    return config_obj->childGroups().contains(map_name);
    }

bool ConfigSettings::contains_structure(QString struct_name)
    {
    return contains_map(struct_name);
    }

bool ConfigSettings::contains_structure_map(QString struct_name, QString map_name)
    {
    config_obj->beginGroup(struct_name);
    bool contained = config_obj->childGroups().contains(map_name);
    config_obj->endGroup();
    return contained;
    }

void ConfigSettings::clear_map(QString map_name)
    {
    config_obj->remove(map_name);
    }

void ConfigSettings::clear_structure(QString struct_name)
    {
    config_obj->remove(struct_name);
    }

QList<QVariant> ConfigSettings::get_list(QString list_name)
    {
    QList<QVariant> list_obj;
    int size = config_obj->beginReadArray(list_name);

    for (int i = 0; i < size; ++i)
        {
        config_obj->setArrayIndex(i);
        list_obj.append(config_obj->value("item"));
        }

    config_obj->endArray();
    return list_obj;
    }

void ConfigSettings::set_list(QString list_name, QList<QVariant> list_obj)
    {
    config_obj->beginWriteArray(list_name);

    for (int i = 0; i < list_obj.size(); ++i)
        {
        config_obj->setArrayIndex(i);
        config_obj->setValue("item", list_obj.at(i));
        }

    config_obj->endArray();
    }

void ConfigSettings::set_map(QString map_name, QMap<QString, QVariant> map_obj)
    {
    config_obj->beginGroup(map_name);

    foreach (QString key, map_obj.keys())
        {
        config_obj->setValue(key, map_obj[key]);
        }

    config_obj->endGroup();
    }

void ConfigSettings::set_structure(QString struct_name, QMap<QString, QMap<QString, QVariant> > struct_obj)
    {
    config_obj->beginGroup(struct_name);

    foreach (QString struct_key, struct_obj.keys())
        {
        config_obj->beginGroup(struct_key);
        QMap<QString, QVariant> item = struct_obj.value(struct_key);

        foreach (QString map_key, item.keys())
            {
            config_obj->setValue(map_key, item.value(map_key));
            }

        config_obj->endGroup();
        }

    config_obj->endGroup();
    }

void ConfigSettings::sync()
    {
    config_obj->sync();
    }

QSettings *ConfigSettings::settings()
    {
    return config_obj;
    }

