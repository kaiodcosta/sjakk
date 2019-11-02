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

#include "sjakkwindow.h"
#include "ui_sjakkwindow.h"

void SjakkWindow::setupGameManager()
    {
    gmanager->setGameTabs(ui->gameTabs);
    gmanager->setInfoManager(imanager);
    }


/**
 * @brief SjakkWindow::loadDefaultSettings
 */
void SjakkWindow::setPreferencesDefaults()
    {
    if (!options->contains("credentials"))
        options->set_map("credentials", QMap<QString, QVariant>());

    if (!options->contains("chess_sets"))
        {
        QMap<QString, QMap<QString, QVariant>> chess_sets;
        QMap<QString, QVariant> set_one;
        set_one.insert("-1", ":/media/pieces/Chess-Basic/Chess_pdt45.svg");
        set_one.insert("-2", ":/media/pieces/Chess-Basic/Chess_kdt45.svg");
        set_one.insert("-3", ":/media/pieces/Chess-Basic/Chess_qdt45.svg");
        set_one.insert("-4", ":/media/pieces/Chess-Basic/Chess_bdt45.svg");
        set_one.insert("-5", ":/media/pieces/Chess-Basic/Chess_ndt45.svg");
        set_one.insert("-6", ":/media/pieces/Chess-Basic/Chess_rdt45.svg");
        set_one.insert("1", ":/media/pieces/Chess-Basic/Chess_plt45.svg");
        set_one.insert("2", ":/media/pieces/Chess-Basic/Chess_klt45.svg");
        set_one.insert("3", ":/media/pieces/Chess-Basic/Chess_qlt45.svg");
        set_one.insert("4", ":/media/pieces/Chess-Basic/Chess_blt45.svg");
        set_one.insert("5", ":/media/pieces/Chess-Basic/Chess_nlt45.svg");
        set_one.insert("6", ":/media/pieces/Chess-Basic/Chess_rlt45.svg");
        chess_sets.insert("chess-basic", set_one);
        options->set_structure("chess_sets", chess_sets);
        }

    QMap<QString, QMap<QString, QVariant>> wgts;

    if (!options->contains("widgets/console"))
        {
        QMap<QString, QVariant> con;
        con.insert("font", "Consolas");
        con.insert("pointsize", 10.0);
        con.insert("wordwrap", 0);
        wgts.insert("console", con);
        }

    if (!options->contains("widgets/mainwindow"))
        {
        QMap<QString, QVariant> con;
        con.insert("size", QSize(1068, 723));
        con.insert("position", QPoint(773, 401));
        wgts.insert("mainwindow", con);
        }

    if (!options->contains("gamesplitter"))
        {
        QList<QVariant> gs;
        gs.append(462);
        gs.append(556);
        options->set_list("gamesplitter", gs);
        }

    if (wgts.count() > 0)
        options->set_structure("widgets", wgts);

    QMap<QString, QMap<QString, QVariant>> cnct;

    if (!options->contains("connection/default"))
        {
        QMap<QString, QVariant> con;
        con.insert("address", "freechess.org");
        con.insert("port", 5000);
        con.insert("timeseal", 1);
        cnct.insert("default", con);
        }

    if (!options->contains("connection/selected"))
        {
        QMap<QString, QVariant> con;
        con.insert("address", "freechess.org");
        con.insert("port", 5000);
        con.insert("user", "guest");
        con.insert("password", "guest");
        con.insert("timeseal", 1);
        con.insert("type", "guest");
        cnct.insert("selected", con);
        }

    if (cnct.count() > 0)
        options->set_structure("connection", cnct);

    QMap<QString, QMap<QString, QVariant>> skr;

    if (!options->contains("seek/default"))
        {
        QMap<QString, QVariant> con;
        con.insert("color", "");
        con.insert("formula", 0);
        con.insert("game_type", 1);
        con.insert("manual", 0);
        con.insert("max_rating", 9999);
        con.insert("min_rating", 0);
        con.insert("rated", 0);
        con.insert("time_min", 3);
        con.insert("time_inc", 2);
        skr.insert("default", con);
        }

    if (skr.count() > 0)
        options->set_structure("seek", skr);

    if (!options->contains("soundfx"))
        {
        QMap<QString, QVariant> snds;
        snds.insert("game_over", ":/media/sounds/game-over.wav");
        snds.insert("piece_moved", ":/media/sounds/chess-move-on-alabaster.wav");
        options->set_map("soundfx", snds);
        }

    if (!options->contains("gameboard"))
        {
        QMap<QString, QVariant> gb;
        gb.insert("dark_square_color", QColor(85, 107, 47, 255));
        gb.insert("light_square_color", QColor(242, 222, 179, 255));
        gb.insert("piece_set", "chess-basic");
        options->set_map("gameboard", gb);
        }
    }

void SjakkWindow::restorePreferences()
    {
    // Set preferences for first time use or in case they got wiped
    setPreferencesDefaults();
    restoreWindowGeometryPrefs();
    restoreConsolePrefs();
    restoreOptionPrefs();
    }

void SjakkWindow::restoreWindowGeometryPrefs()
    {
    QMap<QString, QMap<QString, QVariant>> w = options->get_structure("widgets");
    resize(w["mainwindow"]["size"].toSize());
    move(w["mainwindow"]["position"].toPoint());
    QList<int> gsizes;

    foreach (QVariant i, options->get_list("gamesplitter"))
        gsizes.append(i.toInt());

    ui->gameSplitter->setSizes(gsizes);
    }

void SjakkWindow::restoreConsolePrefs()
    {
    QMap<QString, QMap<QString, QVariant>> w = options->get_structure("widgets");
    ui->outputConsole->setFont(QFont(w["console"]["font"].toString()));
    ui->outputConsole->setFontPointSize(w["console"]["pointsize"].toDouble());
    ui->outputConsole->setWordWrapMode(static_cast<QTextOption::WrapMode>(w["console"]["wordwrap"].toInt()));
    }

void SjakkWindow::restoreOptionPrefs()
    {
    conn_opts = options->get_structure("connection");
    }

void SjakkWindow::savePreferences()
    {
    saveWindowGeometryPrefs();
    }

void SjakkWindow::saveWindowGeometryPrefs()
    {
    QMap<QString, QMap<QString, QVariant>> w;
    w.insert("mainwindow", QMap<QString, QVariant>());
    w["mainwindow"].insert("size", size());
    w["mainwindow"].insert("position", pos());
    options->set_structure("widgets", w);
    QList<QVariant> gs;

    for (int i = 0; i < ui->gameSplitter->sizes().count(); i++)
        gs.append(ui->gameSplitter->sizes().at(i));

    options->set_list("gamesplitter", gs);
    }


void SjakkWindow::makeUiConnections()
    {
    connect(ui->cmdLine, &QLineEdit::returnPressed, this, &SjakkWindow::commandInputEvent);
    connect(ui->cmdLine, &HistoryLineEdit::historyNext, this, &SjakkWindow::commandHistoryNextEvent);
    connect(ui->cmdLine, &HistoryLineEdit::historyPrevious, this, &SjakkWindow::commandHistoryPreviousEvent);
    connect(ui->actionConnect, &QAction::toggled, this, &SjakkWindow::connectClickedEvent);
    connect(ui->infoTabs, &QTabWidget::currentChanged, this, &SjakkWindow::infoTabChangedEvent);
    connect(ui->gameTabs, &QTabWidget::tabCloseRequested, gmanager, &GameManager::gameTabClosedEvent);
    connect(ui->actionAbort, &QAction::triggered, gmanager, &GameManager::RequestAbort);
    connect(ui->actionDraw, &QAction::triggered, gmanager, &GameManager::RequestDraw);
    connect(ui->actionResign, &QAction::triggered, gmanager, &GameManager::Resign);
    connect(ui->actionAdjourn, &QAction::triggered, gmanager, &GameManager::RequestAdjourn);
    connect(refreshGamesListButton, &QPushButton::clicked, this, &SjakkWindow::gamesTabRefreshClicked);
    connect(ui->actionAbout_Sjakk, &QAction::triggered, this, &SjakkWindow::aboutClickedEvent);
    connect(ui->actionSeekGame, &QAction::triggered, this, &SjakkWindow::seekClickedEvent);
    connect(ui->actionSeek1, &QAction::triggered, this, &SjakkWindow::seek1ClickedEvent);
    connect(ui->actionSeek3, &QAction::triggered, this, &SjakkWindow::seek3ClickedEvent);
    connect(ui->actionSeek15, &QAction::triggered, this, &SjakkWindow::seek15ClickedEvent);
    connect(ui->actionPreferences, &QAction::triggered, this, &SjakkWindow::preferencesClickedEvent);
    }
void SjakkWindow::makeSocketConnections()
    {
    connect(socket, &QTcpSocket::readyRead, this, &SjakkWindow::socketReadyReadEvent);
    connect(socket, &QTcpSocket::connected, this, &SjakkWindow::socketConnectedEvent);
    connect(socket, &QTcpSocket::disconnected, this, &SjakkWindow::socketDisconnectedEvent);
    connect(timeseal, &Timeseal::ping_echo, this, &SjakkWindow::timesealPingPong);
    }
void SjakkWindow::makeParserConnections()
    {
    connect(parser, &FicsParser::ficsReadyTextEvent, this, &SjakkWindow::parserReadyTextEvent);
    connect(parser, &FicsParser::ficsLoginPromptEvent, this, &SjakkWindow::parserLoginPromptEvent);
    connect(parser, &FicsParser::ficsPasswordPromptEvent, this, &SjakkWindow::parserPasswordPromptEvent);
    connect(parser, &FicsParser::ficsGuestPromptEvent, this, &SjakkWindow::parserGuestPromptEvent);
    connect(parser, &FicsParser::ficsSessionStartEvent, this, &SjakkWindow::parserSessionStartEvent);
    connect(parser, &FicsParser::ficsStyle12Event, this->gmanager, &GameManager::ficsStyle12Event);
    connect(parser, &FicsParser::ficsGameBannerEndedEvent, this->gmanager, &GameManager::ficsGameBannerEndedEvent);
    connect(parser, &FicsParser::ficsSeekInfoEvent, this->imanager, &InfoManager::ficsSeekInfoEvent);
    connect(parser, &FicsParser::ficsSeekClearEvent, this->imanager, &InfoManager::ficsSeekClearEvent);
    connect(parser, &FicsParser::ficsSeekRemoveEvent, this->imanager, &InfoManager::ficsSeekRemoveEvent);
    connect(parser, &FicsParser::ficsGameListItemEvent, this->imanager, &InfoManager::ficsGameListEvent);
    connect(parser, &FicsParser::ficsGameListEndEvent, this->imanager, &InfoManager::ficsGameListEndEvent);
    connect(parser, &FicsParser::ficsExamListItemEvent, this->imanager, &InfoManager::ficsExamListEvent);
    connect(parser, &FicsParser::ficsGameBannerStartedEvent, this->imanager, &InfoManager::ficsGameBannerStartedEvent);
    connect(parser, &FicsParser::ficsGameListItemEvent, this->gmanager, &GameManager::ficsGameListItemEvent);
    connect(parser, &FicsParser::ficsGameBannerEndedEvent, this->imanager, &InfoManager::ficsGameBannerEndedEvent);
    }
void SjakkWindow::makeGameManagerConnections()
    {
    connect(gmanager, &GameManager::signalSocketWriteRequest, this, &SjakkWindow::socketWriteRequestEvent);
    connect(gmanager, &GameManager::signalMyGameStarted, imanager, &InfoManager::myGameStartedEvent);
    }
void SjakkWindow::makeInfoManagerConnections()
    {
    connect(imanager, &InfoManager::socketWriteRequest, this, &SjakkWindow::socketWriteRequestEvent);
    }
void SjakkWindow::writeConsole(QByteArray msg, int color, int weight)
    {
    ui->outputConsole->moveCursor(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);
    ui->outputConsole->setTextColor(QColor(static_cast<Qt::GlobalColor>(color)));
    ui->outputConsole->setFontWeight(weight);
    ui->outputConsole->insertPlainText(msg);
    }
void SjakkWindow::writeConsoleLine(QByteArray msg, int color, int weight)
    {
    ui->outputConsole->moveCursor(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);
    ui->outputConsole->setTextColor(QColor(static_cast<Qt::GlobalColor>(color)));
    ui->outputConsole->setFontWeight(weight);
    ui->outputConsole->insertPlainText(msg.append('\n'));
    }
void SjakkWindow::writeSocketLine(QByteArray msg)
    {
    if (socket->state() == QTcpSocket::ConnectedState)
        {
        if (conn_opts["selected"]["timeseal"].toBool())
            {
            QByteArray stamp_msg = timeseal->stamp(msg);
            socket->write(stamp_msg);
            }
        else
            {
            msg.append('\n');
            socket->write(msg);
            }
        }
    }
void SjakkWindow::commandInputEvent()
    {
    if (this->socket->state() == QTcpSocket::ConnectedState)
        writeSocketLine(QByteArray(QString(ui->cmdLine->text()).toLatin1()).data());

    writeConsoleLine(ui->cmdLine->text().toLatin1(), Qt::GlobalColor::blue, QFont::Black);
    ui->cmdLine->setText("");
    }
void SjakkWindow::commandHistoryNextEvent(QString msg)
    {
    ui->cmdLine->setText(msg);
    }
void SjakkWindow::commandHistoryPreviousEvent(QString msg)
    {
    ui->cmdLine->setText(msg);
    }
void SjakkWindow::connectClickedEvent(bool checked)
    {
    if (checked)
        {
        if (socket->state() != QAbstractSocket::ConnectedState)
            {
            ConnectDialog connect_dialog(this);
            int result = connect_dialog.exec();
            conn_opts = options->get_structure("connection");

            if (result == QDialog::DialogCode::Accepted)
                {
                if (conn_opts["default"]["timeseal"].toBool())
                    {
                    parser->timeseal = timeseal;
                    timeseal_status.setText("Timeseal ON");
                    }
                else
                    {
                    parser->timeseal = nullptr;
                    timeseal_status.setText("Timeseal OFF");
                    }

                QString address = conn_opts["selected"]["address"].toString();
                ushort port = static_cast<ushort>(conn_opts["selected"]["port"].toInt());
                socket->connectToHost(address, port);
                }

            if (result == QDialog::DialogCode::Rejected)
                ui->actionConnect->setChecked(false);
            }
        }
    else
        {
        if (this->socket->state() == QTcpSocket::ConnectedState)
            {
            ui->statusBar->showMessage("Disconnecting...");
            ui->statusBar->showMessage("Leaving server");
            writeSocketLine("quit");
            }
        else
            {
            ui->statusBar->showMessage("Already disconnected!");
            this->loggedIn = false;
            }
        }
    }
void SjakkWindow::aboutClickedEvent(bool checked)
    {
    (void)checked;
    AboutDialog about_dialog(this);
    about_dialog.exec();
    }
void SjakkWindow::seekClickedEvent(bool checked)
    {
    (void)checked;
    SeekDialog seek_dialog(this);
    int result = seek_dialog.exec();
    QString seek_ad;

    if (result == QDialog::DialogCode::Accepted)
        writeSocketLine(seek_dialog.getSeekRequest());
    }
void SjakkWindow::seek1ClickedEvent(bool checked)
    {
    (void)checked;
    writeSocketLine("seek 1 0");
    }
void SjakkWindow::seek3ClickedEvent(bool checked)
    {
    (void)checked;
    writeSocketLine("seek 3 0");
    }
void SjakkWindow::seek15ClickedEvent(bool checked)
    {
    (void)checked;
    writeSocketLine("seek 15 0");
    }
void SjakkWindow::preferencesClickedEvent(bool checked)
    {
    (void)checked;
    PreferencesDialog pref_dialog(this);
    int result = pref_dialog.exec();

    if (result == QDialog::DialogCode::Accepted)
        restoreConsolePrefs();
    }
void SjakkWindow::RequestGamesList()
    {
    if (this->loggedIn && socket->state() == QAbstractSocket::ConnectedState)
        {
        imanager->ficsGameListClearEvent();
        writeSocketLine("games");
        }
    }
void SjakkWindow::infoTabChangedEvent(int index)
    {
    QWidget *wdgt = ui->infoTabs->widget(index);

    if (wdgt == nullptr)
        return;

    if (wdgt == ui->gamesTab)
        {
        refreshGamesListButton->setVisible(true);
        RequestGamesList();
        }
    else
        refreshGamesListButton->setVisible(false);
    }
void SjakkWindow::socketReadyReadEvent()
    {
    this->receivedData.clear();
    this->receivedData.append(socket->readAll());
    qInfo().noquote() << receivedData;

    if (!loggedIn)
        this->parser->parseAuthentication(receivedData);
    else
        this->parser->parseServerData(receivedData);
    }
void SjakkWindow::socketConnectedEvent()
    {
    if (conn_opts["default"]["timeseal"].toBool())
        writeSocketLine(timeseal->hello());

    writeConsoleLine("Connected to server", Qt::GlobalColor::blue);
    }
void SjakkWindow::socketDisconnectedEvent()
    {
    writeConsoleLine("Disconnected from server", Qt::GlobalColor::blue);
    this->loggedIn = false;
    gmanager->serverDisconnect();
    }
void SjakkWindow::socketWriteRequestEvent(QString data)
    {
    writeSocketLine(data.toLatin1());
    }
void SjakkWindow::timesealPingPong(QByteArray ack)
    {
    writeSocketLine(ack);
    }
void SjakkWindow::parserReadyTextEvent(QByteArray buffer)
    {
    ui->outputConsole->moveCursor(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);
    ui->outputConsole->setTextColor(QColor(Qt::GlobalColor::black));
    ui->outputConsole->setFontWeight(QFont::Normal);
    ui->outputConsole->insertPlainText(QString(buffer));
    }
void SjakkWindow::parserLoginPromptEvent()
    {
    if (conn_opts["selected"]["type"].toString() == "guest")
        writeSocketLine("guest");
    else
        writeSocketLine(QString("%1").arg(conn_opts["selected"]["user"].toString()).toLatin1());
    }
void SjakkWindow::parserPasswordPromptEvent()
    {
    writeSocketLine(QString("%1").arg(conn_opts["selected"]["password"].toString()).toLatin1());
    }
void SjakkWindow::parserGuestPromptEvent()
    {
    ui->statusBar->showMessage("Guest login accepted");
    writeSocketLine("");
    }
void SjakkWindow::parserSessionStartEvent()
    {
    ui->statusBar->showMessage("session started");
    this->loggedIn = true;
    writeSocketLine("set seek 0");
    writeSocketLine("iset seekremove 1");
    writeSocketLine("iset seekinfo 1");
    writeSocketLine("set style 12");
    writeSocketLine("set gin 1");
    writeSocketLine("set bell off");
    QString interface_str = QString("set interface %1 %2 %3.%4.%5")
                            .arg(MY_APPNAME)
                            .arg(MY_VERSIONYEAR)
                            .arg(MY_VERSIONMAJOR)
                            .arg(MY_VERSIONMINOR)
                            .arg(MY_VERSIONBUILD);
    writeSocketLine(interface_str.toLatin1());
    }

void SjakkWindow::gamesTabRefreshClicked()
    {
    RequestGamesList();
    }
void SjakkWindow::consoleActionLineWrap(bool checked)
    {
    ui->outputConsole->setLineWrapMode(checked ? QTextEdit::LineWrapMode::WidgetWidth : QTextEdit::LineWrapMode::NoWrap);
    }
void SjakkWindow::Debug1()
    {
    }
void SjakkWindow::closeEvent(QCloseEvent *event)
    {
    if (this->socket)
        delete socket;

    if (this->parser)
        delete parser;

    savePreferences();
    event->accept();
    }
SjakkWindow::SjakkWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SjakkWindow),
    gmanager(new GameManager(this)),
    imanager(new InfoManager(this)),
    socket(new QTcpSocket(this)),
    parser(new FicsParser(this)),
    timeseal(new Timeseal(this))
    {
    ui->setupUi(this);
    options = ConfigSettings::Instance();
    restorePreferences();
    ui->outputConsole->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
    ui->outputConsole->document()->setMaximumBlockCount(1000);
    refreshGamesListButton = new QPushButton(QIcon(":/media/icons/Becris/refresh.svg"), "Refresh List", ui->infoTabs);
    ui->infoTabs->setCornerWidget(refreshGamesListButton, Qt::Corner::TopRightCorner);

    if (ui->infoTabs->currentWidget() == ui->gamesTab)
        refreshGamesListButton->setVisible(true);
    else
        refreshGamesListButton->setVisible(false);

    loggedIn = false;
    setupInfoManager();
    setupGameManager();
    ui->infoTabs->setCurrentIndex(0);
    makeUiConnections();
    makeSocketConnections();
    makeParserConnections();
    makeGameManagerConnections();
    makeInfoManagerConnections();

    if (conn_opts["selected"]["timeseal"].toBool())
        {
        timeseal_status.setText("Timeseal ON");
        parser->timeseal = timeseal;
        }
    else
        {
        timeseal_status.setText("Timeseal OFF");
        parser->timeseal = nullptr;
        }

    ui->statusBar->addPermanentWidget(&timeseal_status);
    }
SjakkWindow::~SjakkWindow()
    {
    delete ui;
    }
void SjakkWindow::setupInfoManager()
    {
    this->imanager->setSeekerTableModel(ui->seekersTable);
    this->imanager->setGameInfoTableModel(ui->gamesTable);
    }
