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

#ifndef SJAKKWINDOW_H
#define SJAKKWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QAbstractSocket>
#include <QtNetwork>
#include <QDebug>
#include <QPushButton>
#include <QPixmap>
#include <QString>
#include <QStringLiteral>
#include <QSoundEffect>
#include <QSound>
#include <QStandardPaths>
#include "dialogs/connectdialog.h"
#include "game/gamemanager.h"
#include "infomanager.h"
#include "fics/ficsparser.h"
#include "configsettings.h"
#include "dialogs/aboutdialog.h"
#include "dialogs/seekdialog.h"
#include "dialogs/preferencesdialog.h"
#include "timeseal/timeseal.h"
#include "config.h"

namespace Ui
{
class SjakkWindow;
}

class SjakkWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit SjakkWindow(QWidget *parent = nullptr);
        ~SjakkWindow() override;

    private:
        Ui::SjakkWindow *ui;
        GameManager *gmanager;
        InfoManager *imanager;
        QTcpSocket *socket;
        FicsParser *parser;
        Timeseal *timeseal;

        QByteArray receivedData;
        QPushButton *refreshGamesListButton;
        QLabel timeseal_status;
        bool loggedIn;

        // Cached flags from options
        bool use_timeseal;
        // End cached flags

        ConfigSettings *options;
        QString config_file = QStringLiteral("./sjakk.json");

        void setupInfoManager();
        void setupGameManager();

        void setPreferencesDefaults();
        void restorePreferences();
        void restoreWindowGeometryPrefs();
        void restoreConsolePrefs();
        void restoreOptionPrefs();
        void savePreferences();
        void saveWindowGeometryPrefs();

        void makeUiConnections();
        void makeSocketConnections();
        void makeParserConnections();
        void makeGameManagerConnections();
        void makeInfoManagerConnections();

        void writeConsole(QByteArray msg, int color = Qt::GlobalColor::black, int weight = QFont::Normal);
        void writeConsoleLine(QByteArray msg, int color = Qt::GlobalColor::black, int weight = QFont::Normal);
        void writeSocketLine(QByteArray msg);

        QMap<QString, QMap<QString, QVariant>> conn_opts;

    public slots:
        void commandInputEvent();
        void commandHistoryNextEvent(QString msg);
        void commandHistoryPreviousEvent(QString msg);
        void connectClickedEvent(bool checked);
        void aboutClickedEvent(bool checked);
        void seekClickedEvent(bool checked);
        void seek1ClickedEvent(bool checked);
        void seek3ClickedEvent(bool checked);
        void seek15ClickedEvent(bool checked);
        void preferencesClickedEvent(bool checked);
        void infoTabChangedEvent(int index);

        void socketReadyReadEvent();
        void socketConnectedEvent();
        void socketDisconnectedEvent();
        void socketWriteRequestEvent(QString data);
        void timesealPingPong(QByteArray ack);

        void parserReadyTextEvent(QByteArray buffer);
        void parserLoginPromptEvent();
        void parserPasswordPromptEvent();
        void parserGuestPromptEvent();
        void parserSessionStartEvent();

        void gamesTabRefreshClicked();
        void consoleActionLineWrap(bool checked);

        void Debug1();

        void RequestGamesList();

    protected:
        void closeEvent(QCloseEvent *event) override;
    };

#endif // SJAKKWINDOW_H
