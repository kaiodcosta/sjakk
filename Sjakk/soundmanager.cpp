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

#include "soundmanager.h"

SoundManager::SoundManager(QObject *parent) : QObject(parent)
    {
    options = ConfigSettings::Instance();
    LoadDefaultEfx();
    }

void SoundManager::LoadDefaultEfx()
    {
    QMap<QString, QVariant> soundfx = options->get_map("soundfx");

    foreach (QString key, soundfx.keys())
        sound_efx.insert(key, new QSound(soundfx[key].toString()));
    }

void SoundManager::PlaySoundEfx(QString name)
    {
    if (sound_efx.contains(name))
        sound_efx[name]->play();
    }
