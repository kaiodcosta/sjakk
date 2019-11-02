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

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QMap>
#include <QSoundEffect>
#include <QSound>
#include "configsettings.h"

class SoundManager : public QObject
    {
        Q_OBJECT

    private:
        QMap<QString, QSound *> sound_efx;
        ConfigSettings *options;

    public:
        explicit SoundManager(QObject *parent = nullptr);
        void LoadDefaultEfx();
        void PlaySoundEfx(QString name);

    signals:

    public slots:
    };

#endif // SOUNDMANAGER_H
