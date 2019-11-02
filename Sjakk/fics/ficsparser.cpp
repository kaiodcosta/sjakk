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

#include "ficsparser.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QtDebug>
#include <QString>

FicsParser::FicsParser(QObject *parent) : QObject(parent)
    {
    lastMatchedGameListItem = false;
    databuffer.clear();
    timeseal = nullptr;
    ficsPromptRgx           = new QRegularExpression(R"foo(^fics%\s(.*)$)foo");
    ficsStyle12Regx         = new QRegularExpression(R"foo(^<12>\s(.{8})\s(.{8})\s(.{8})\s(.{8})\s(.{8})\s(.{8})\s(.{8})\s(.{8})\s([WB])\s([0-7\\-]+)\s(.{1})\s(.{1})\s(.{1})\s(.{1})\s([0-9]+)\s([0-9]+)\s(\w+)\s(\w+)\s([\-0-9]+)\s([\-0-9]+)\s([\-0-9]+)\s([\-0-9]+)\s([\-0-9]+)\s([\-0-9]+)\s([\-0-9]+)\s([\-0-9]+)\s([A-Za-z0-9/-]+)\s\(([\-0-9]+):([\-0-9]+)\)\s([0-9a-zA-Z\+\-\#]+)\s(.{1})\s(.{1})\s([\-0-9]+))foo");
    ficsSeekInfoRegx        = new QRegularExpression(R"foo(^<s>\s([0-9]+)\sw=(\w+)\sti=(\w+)\srt=([0-9]+)(.)\st=([0-9]+)\si=([0-9]+)\sr=(.)\stp=(.*)\sc=(.)\srr=([0-9]+)-([0-9]+)\sa=(.)\sf=(.))foo");
    ficsSeekClearRegx       = new QRegularExpression(R"foo(^<sc>)foo");
    ficsSeekRemoveRegx      = new QRegularExpression(R"foo(^<sr>\s(.*))foo");
    ficsGameListItemRegx    = new QRegularExpression(R"foo(^\s*([0-9]+)\s+([0-9+\\-]+)\s+(\w+)\s+([0-9+\\-]+)\s+(\w+)\s+\[(.{1})(.{1})(.{1})\s+([0-9]+)\s*([0-9]+)\]\s*([0-9:]+)\s*-\s*([0-9:]+)\s+\(\s*(\w+)\s*-\s*(\w+)\)\s+([WB]):\s*([0-9]+))foo");
    ficsExamListItemRegx    = new QRegularExpression(R"foo(^\s*([0-9]+)\s+\((Exam\.)\s+([0-9]+)\s+(\w+)\s+([0-9]+)\s+(\w+)\s*\)\s+\[(.{1})(.{1})(.{1})\s*([0-9]+)\s+([0-9]+)\]\s*([WB]):\s*([0-9]+))foo");
    ficsGameListEndRegex    = new QRegularExpression(R"foo(^\s*[0-9]+\sgame(s{1})?\sdisplayed(.*)$)foo");
    ficsGameBannerRegex     = new QRegularExpression(R"foo(^{Game\s([0-9]+)\s+\((.*)\)(.*)}(.*))foo");
    ficsVarsBannerRegex     = new QRegularExpression(R"foo()foo");
    emptyLineRegex          = new QRegularExpression(R"foo(^\s*$)foo");
    }

FicsParser::~FicsParser()
    {
    }

void FicsParser::parseAuthentication(QByteArray ba)
    {
    QByteArray parsebuffer;     // This is used for parsing only
    QByteArray linebuffer;      // The current line
    parsebuffer += databuffer + ba; // Transfer new data to parsebuffer along with leftover from databuffer
    databuffer.clear();

    if (timeseal != nullptr)
        timeseal->process(parsebuffer);

    for (int i = 0; i < parsebuffer.size(); i++)
        {
        switch (parsebuffer[i])
            {
            case '\r':
                continue;

            case '\n':
                emit ficsReadyTextEvent(linebuffer + '\n');

                if (linebuffer.startsWith("**** Starting FICS session as"))
                    emit ficsSessionStartEvent();

                linebuffer.clear();
                break;

            case ':':
                linebuffer.append(':');
                emit ficsReadyTextEvent(linebuffer);

                if (linebuffer.startsWith("login:"))
                    emit ficsLoginPromptEvent();

                if (linebuffer.startsWith("Press return to enter the server as"))
                    emit ficsGuestPromptEvent();

                if (linebuffer.startsWith("password:"))
                    emit ficsPasswordPromptEvent();

                linebuffer.clear();
                break;

            default:
                linebuffer.append(parsebuffer[i]);
                break;
            }
        }

    if (linebuffer.isEmpty() == false)
        {
        databuffer.prepend(linebuffer);
        linebuffer.clear();
        }
    }

void FicsParser::parseServerData(QByteArray ba)
    {
    QByteArray parsebuffer;     // This is used for parsing only
    QByteArray linebuffer;      // The current line
    parsebuffer += databuffer + ba; // Transfer new data to parsebuffer along with leftover from databuffer
    databuffer.clear();

    if (timeseal != nullptr)
        timeseal->process(parsebuffer);

    for (int i = 0; i < parsebuffer.size(); i++)
        {
        switch (parsebuffer[i])
            {
            case '\r':
                continue;

            case '\n':
                if (processFicsLine(linebuffer) == false)
                    emit ficsReadyTextEvent(linebuffer + '\n');

                linebuffer.clear();
                break;

            default:
                linebuffer.append(parsebuffer[i]);
                break;
            }
        }

    if (linebuffer.isEmpty() == false)
        {
        databuffer.prepend(linebuffer);
        linebuffer.clear();
        }
    }

bool FicsParser::matchesFicsInformation(QByteArray ba)
    {
    QRegularExpressionMatch m1 = ficsPromptRgx->match(ba);

    if (m1.hasMatch())
        {
        if (m1.captured(1) != "")
            emit ficsReadyTextEvent(m1.captured(1).toUtf8() + "\n");

        //emit ficsInformationEvent(m1.captured(1));
        return true;
        }

    return false;
    }

bool FicsParser::matchesFicsStyle12(QByteArray ba)
    {
    QRegularExpressionMatch m1 = ficsStyle12Regx->match(ba);

    if (m1.hasMatch())
        {
        FicsStyle12 *game = new FicsStyle12();
        int rankindex = 1;

        for (int rank = 7; rank >= 0; rank--)
            {
            QString singlerank = m1.captured(rankindex);

            for (int file = 0; file < 8; file++)
                game->setPieceOnBoard(GameFlags::ConvertToPieceType(singlerank[file]), file, rank);

            rankindex++;
            }

        if (m1.captured(9) == "W")
            game->setWhiteToMove(true);
        else
            game->setWhiteToMove(false);

        game->setEPFile(m1.captured(10).toInt());
        game->setCanWhiteCastleShort(m1.captured(11).toInt() == 1 ? true : false);
        game->setCanWhiteCastleLong(m1.captured(12).toInt() == 1 ? true : false);
        game->setCanBlackCastleShort(m1.captured(13).toInt() == 1 ? true : false);
        game->setCanBlackCastleLong(m1.captured(14).toInt() == 1 ? true : false);
        game->setHalfMoveCount(m1.captured(15).toInt());
        game->setGameID(m1.captured(16).toInt());
        game->setWhiteName(m1.captured(17));
        game->setBlackName(m1.captured(18));
        game->setMyRelation(static_cast<FicsStyle12::GameRelation>(m1.captured(19).toInt()));
        game->setTimeMinutes(m1.captured(20).toInt());
        game->setTimeIncrementSeconds(m1.captured(21).toInt());
        game->setWhiteMaterial(m1.captured(22).toInt());
        game->setBlackMaterial(m1.captured(23).toInt());
        game->setWhiteRemainingTimeSeconds(m1.captured(24).toInt());
        game->setBlackRemainingTimeSeconds(m1.captured(25).toInt());
        game->setMoveAboutToBeMade(m1.captured(26).toInt());
        game->setVerboseCoordinateNotationPreviousMove(m1.captured(27));
        game->setTimeMinutesPreviousMove(m1.captured(28).toInt());
        game->setTimeSecondsPreviousMove(m1.captured(29).toInt());
        game->setPrettyNotationPreviousMove(m1.captured(30));
        game->setBlackAtBottom(m1.captured(31).toInt() == 1 ? true : false);
        game->setClockTicking(m1.captured(32).toInt() == 1 ? true : false);
        game->setLagTimeMilliseconds(m1.captured(33).toInt());
        emit ficsStyle12Event(game);
        return true;
        }

    return false;
    }

bool FicsParser::matchesFicsSeekInfo(QByteArray ba)
    {
    QRegularExpressionMatch m1 = ficsSeekInfoRegx->match(ba);

    if (m1.hasMatch())
        {
        FicsSeeker *seeker = new FicsSeeker();
        seeker->setSeekerIndex(m1.captured(1).toInt());
        seeker->setSeekerFromName(m1.captured(2));
        seeker->setSeekerTitles(m1.captured(3));
        seeker->setSeekerRating(m1.captured(4).toInt());
        seeker->setSeekerRatingType(m1.captured(5));
        seeker->setSeekerTimeControl(m1.captured(6).toInt());
        seeker->setSeekerTimeIncrement(m1.captured(7).toInt());
        seeker->setSeekerIsRated(m1.captured(8) == "r" ? true : false);
        seeker->setSeekerGameType(m1.captured(9));
        seeker->setSeekerColorRequest(m1.captured(10));
        seeker->setSeekerRatingMin(m1.captured(11).toInt());
        seeker->setSeekerRatingMax(m1.captured(12).toInt());
        seeker->setSeekerStartAutomatic(m1.captured(13) == "t" ? true : false);
        seeker->setSeekerFormulaChecked(m1.captured(14) == "t" ? true : false);
        emit ficsSeekInfoEvent(seeker);
        return true;
        }

    return false;
    }

bool FicsParser::matchesFicsSeekRemove(QByteArray ba)
    {
    QRegularExpressionMatch m1 = ficsSeekRemoveRegx->match(ba);

    if (m1.hasMatch())
        {
        QList<int> *seekindices = new QList<int>();
        QStringList sl = m1.captured(1).split(" ", QString::SkipEmptyParts);

        for (int i = 0; i < sl.size(); i++)
            seekindices->append(sl.at(i).toInt());

        emit ficsSeekRemoveEvent(seekindices);
        return true;
        }

    return false;
    }

bool FicsParser::matchesFicsSeekClear(QByteArray ba)
    {
    QRegularExpressionMatch m1 = ficsSeekClearRegx->match(ba);

    if (m1.hasMatch())
        {
        emit ficsSeekClearEvent();
        return true;
        }

    return false;
    }

bool FicsParser::matchesFicsExamListItem(QByteArray ba)
    {
    QRegularExpressionMatch m1 = ficsExamListItemRegx->match(ba);

    if (m1.hasMatch())
        {
        FicsGameInfo *ginfo = new FicsGameInfo();
        ginfo->setIsExamined(true);
        ginfo->setGameID(m1.captured(1).toInt());
        ginfo->setWhiteRating(m1.captured(3));
        ginfo->setWhiteName(m1.captured(4));
        ginfo->setBlackRating(m1.captured(5));
        ginfo->setBlackName(m1.captured(6));
        ginfo->setIsPrivate(m1.captured(7) == "p" ? true : false);
        ginfo->setGameCategory(m1.captured(8));
        ginfo->setIsRated(m1.captured(9) == "r" ? true : false);
        ginfo->setTimeMinutes(m1.captured(10).toInt());
        ginfo->setTimeIncrement(m1.captured(11).toInt());
        ginfo->setIsWhiteOnMove(m1.captured(12) == "W" ? true : false);
        ginfo->setMoveNumber(m1.captured(13).toInt());
        emit ficsGameListItemEvent(ginfo);
        return true;
        }

    return false;
    }

bool FicsParser::matchesFicsGameListItem(QByteArray ba)
    {
    QRegularExpressionMatch m1 = ficsGameListItemRegx->match(ba);

    if (m1.hasMatch())
        {
        FicsGameInfo *ginfo = new FicsGameInfo();
        ginfo->setGameID(m1.captured(1).toInt());
        ginfo->setWhiteRating(m1.captured(2));
        ginfo->setWhiteName(m1.captured(3));
        ginfo->setBlackRating(m1.captured(4));
        ginfo->setBlackName(m1.captured(5));
        ginfo->setIsPrivate(m1.captured(6) == "p" ? true : false);
        ginfo->setGameCategory(m1.captured(7));
        ginfo->setIsRated(m1.captured(8) == "r" ? true : false);
        ginfo->setTimeMinutes(m1.captured(9).toInt());
        ginfo->setTimeIncrement(m1.captured(10).toInt());
        ginfo->setWhiteClockTime(m1.captured(11));
        ginfo->setBlackClockTime(m1.captured(12));
        ginfo->setWhiteMaterial(m1.captured(13).toInt());
        ginfo->setBlackMaterial(m1.captured(14).toInt());
        ginfo->setIsWhiteOnMove(m1.captured(15) == "W" ? true : false);
        ginfo->setMoveNumber(m1.captured(16).toInt());
        lastMatchedGameListItem = true;
        emit ficsGameListItemEvent(ginfo);
        return true;
        }

    return false;
    }

bool FicsParser::matchesFicsGameListEnd(QByteArray ba)
    {
    QRegularExpressionMatch m1 = ficsGameListEndRegex->match(ba);

    if (m1.hasMatch())
        {
        emit ficsGameListEndEvent();
        return true;
        }

    return false;
    }

bool FicsParser::matchesFicsGameBanner(QByteArray ba)
    {
    QRegularExpressionMatch m1 = ficsGameBannerRegex->match(ba);

    if (m1.hasMatch())
        {
        FicsBannerInfo *banner = new FicsBannerInfo();
        //FicsGameInfo *ginfo = new FicsGameInfo();
        //ginfo->setGameID(m1.captured(1).toInt());
        banner->setGameID(m1.captured(1).toInt());
        banner->setBannerTitle(m1.captured(2));
        banner->setBannerDescription(m1.captured(3));
        banner->setBannerResult(m1.captured(4));

        if (m1.capturedLength(4) == 0)
            {
            emit ficsGameBannerStartedEvent(banner);
            return true;
            }
        else
            {
            emit ficsGameBannerEndedEvent(banner);
            return true;
            }
        }

    return false;
    }

bool FicsParser::matchesEmptyLine(QByteArray ba)
    {
    QRegularExpressionMatch m1 = emptyLineRegex->match(ba);

    if (m1.hasMatch())
        return true;

    return false;
    }


bool FicsParser::processFicsLine(QByteArray ba)
    {
    if (matchesFicsInformation(ba))
        return true;

    if (matchesFicsStyle12(ba))
        return true;

    if (matchesFicsSeekInfo(ba))
        return true;

    if (matchesFicsSeekRemove(ba))
        return true;

    if (matchesFicsSeekClear(ba))
        return true;

    if (matchesFicsGameListItem(ba))
        return true;

    if (matchesFicsExamListItem(ba))
        return true;

    if (matchesFicsGameListEnd(ba))
        return true;

    if (matchesFicsGameBanner(ba))
        return true;

    if (lastMatchedGameListItem == true)
        {
        lastMatchedGameListItem = false;

        if (matchesEmptyLine(ba))
            return true;
        }

    return false;
    }

