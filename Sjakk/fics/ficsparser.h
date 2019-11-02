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

#ifndef FICSPARSER_H
#define FICSPARSER_H

#include <QObject>
#include "ficsstyle12.h"
#include "ficsgameinfo.h"
#include "ficsseeker.h"
#include "ficsbannerinfo.h"
#include "../game/gameflags.h"
#include "../timeseal/timeseal.h"

class FicsParser : public QObject
    {
        Q_OBJECT
    public:
        explicit FicsParser(QObject *parent = nullptr);
        ~FicsParser();
        void parseAuthentication(QByteArray ba);
        void parseServerData(QByteArray ba);
        bool processFicsLine(QByteArray ba);

        Timeseal *timeseal;

        //bool GamesCommandIssued;


    private:
        // new data goes to this buffer before parsing.
        // TODO: Implement semaphore/mutex to allow FicsParser to run in separate thread
        bool lastMatchedGameListItem;

        QByteArray databuffer;
        QRegularExpression *ficsPromptRgx;
        QRegularExpression *ficsStyle12Regx;
        QRegularExpression *ficsSeekInfoRegx;
        QRegularExpression *ficsSeekRemoveRegx;
        QRegularExpression *ficsSeekClearRegx;
        QRegularExpression *ficsGameListItemRegx;
        QRegularExpression *ficsExamListItemRegx;
        QRegularExpression *ficsGameListEndRegex;
        QRegularExpression *ficsGameBannerRegex;
        QRegularExpression *ficsVarsBannerRegex;
        QRegularExpression *emptyLineRegex;

        bool matchesFicsInformation(QByteArray ba);
        bool matchesFicsStyle12(QByteArray ba);
        bool matchesFicsSeekInfo(QByteArray ba);
        bool matchesFicsSeekRemove(QByteArray ba);
        bool matchesFicsSeekClear(QByteArray ba);
        bool matchesFicsExamListItem(QByteArray ba);
        bool matchesFicsGameListItem(QByteArray ba);
        bool matchesFicsGameListEnd(QByteArray ba);
        bool matchesFicsGameBanner(QByteArray ba);
        bool matchesEmptyLine(QByteArray ba);

    signals:
        void ficsReadyTextEvent(QByteArray buffer);
        void ficsLoginPromptEvent();
        void ficsPasswordPromptEvent();
        void ficsGuestPromptEvent();
        void ficsSessionStartEvent();
        void ficsInformationEvent(QString info);
        void ficsStyle12Event(FicsStyle12 *gdata);
        void ficsSeekInfoEvent(FicsSeeker *seeker);
        void ficsSeekClearEvent();
        void ficsSeekRemoveEvent(QList<int> *removelist);
        void ficsGameListEndEvent();
        void ficsGameListItemEvent(FicsGameInfo *ginfo);
        void ficsExamListItemEvent(FicsGameInfo *ginfo);
        void ficsGameBannerStartedEvent(FicsBannerInfo *binfo);
        void ficsGameBannerEndedEvent(FicsBannerInfo *binfo);

    public slots:

    };

#endif // FICSPARSER_H
