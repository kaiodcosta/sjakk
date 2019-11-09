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

#include "gameboard.h"
#include "ui_gameboard.h"

GameBoard::GameBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameBoard)
    {
    ui->setupUi(this);
    options = ConfigSettings::Instance();
    this->ui->label_top_name->setAttribute(Qt::WA_TranslucentBackground);
    this->loadPieceSet();
    QMap<QString, QVariant> board_options = options->get_map("gameboard");
    ui->chessBoardWidget->setDarkSquareColor(board_options["dark_square_color"].value<QColor>());
    ui->chessBoardWidget->setLightSquareColor(board_options["light_square_color"].value<QColor>());
    connect(ui->chessBoardWidget, &ChessBoard::signalChessMove, this,
            &GameBoard::chessMoveEvent);
    }

GameBoard::~GameBoard()
    {
    delete ui;
    }

FicsStyle12 *GameBoard::PositionData() const
    {
    return m_PositionData;
    }

void GameBoard::loadPieceSet()
    {
    QMap<QString, QVariant> board_options = options->get_map("gameboard");
    QMap<QString, QMap<QString, QVariant>> chess_sets = options->get_structure("chess_sets");

    foreach (QString k, chess_sets[board_options["piece_set"].toString()].keys())
        {
        GameFlags::PieceType ptype = static_cast<GameFlags::PieceType>(k.toInt());
        QString resource_name = chess_sets[board_options["piece_set"].toString()][k].toString();
        ui->chessBoardWidget->setChessPieceIcon(ptype, QIcon(resource_name));
        }
    }

void GameBoard::setPositionData(FicsStyle12 *PositionData)
    {
    m_PositionData = PositionData;
    }


void GameBoard::StopClocks()
    {
    this->ui->topPlayerClockLCD->StopCountDown();
    this->ui->bottomPlayerClockLCD->StopCountDown();
    }


GameFlags::GameClose GameBoard::CanClose() const
    {
    return m_CanClose;
    }

bool GameBoard::GameOver() const
    {
    return m_GameOver;
    }

void GameBoard::FicsStyle12Event(FicsStyle12 *fics_style12, bool is_update)
    {
    if (IAmPlayingGame(fics_style12->MyRelation()))
        {
        setCanClose(GameFlags::GameClose::PromptFirst);
        }
    else
        {
        setCanClose(GameFlags::GameClose::CloseAllowed);
        }

    this->setPositionData(fics_style12);
    this->ui->chessBoardWidget->putPosition(m_PositionData->Position());
    this->updateLastMoved();
    this->updateClocks();
    this->updateStrengths();
    this->updateLag();
    ui->chessBoardWidget->setIsMyMove(fics_style12->IsMyMove());

    if (is_update)
        {
        return;
        }

    m_GameOver = false;

    if (fics_style12->MyColor() == GameFlags::PlayerColor::White)
        {
        ui->chessBoardWidget->setWhiteOnTop(false);
        }
    else
        {
        ui->chessBoardWidget->setWhiteOnTop(true);
        }

    switch (this->PositionData()->MyRelation())
        {
        case FicsStyle12::GameRelation::IAMEXAMINER:
            this->ui->chessBoardWidget->setAcceptMouseInput(GameFlags::AcceptMouse::AcceptAny);
            break;

        case FicsStyle12::GameRelation::IAMPLAYINGMYMOVE:
        case FicsStyle12::GameRelation::IAMPLAYINGOPPONENTMOVE:
            this->ui->chessBoardWidget->setAcceptMouseInput(GameFlags::ConvertToAcceptMouse(
                        fics_style12->MyColor()));
            break;

        default:
            this->ui->chessBoardWidget->setAcceptMouseInput(GameFlags::AcceptMouse::AcceptNone);
        }
    }

void GameBoard::setCanClose(GameFlags::GameClose CanClose)
    {
    m_CanClose = CanClose;
    }

void GameBoard::chessMoveEvent(GameFlags::PieceType source_piece, int fromFile,
                               int fromRank, GameFlags::PieceType target_piece, int toFile, int toRank)
    {
    (void)source_piece;
    (void)target_piece;
    emit signalChessMove(fromFile, fromRank, toFile, toRank);
    }

void GameBoard::updateGameInfo(FicsGameInfo *ginfo)
    {
    if (m_GameOver)
        {
        return;
        }

    QString relation;

    switch (m_PositionData->MyRelation())
        {
        case FicsStyle12::IAMEXAMINER:
            relation = "examining";
            break;

        case FicsStyle12::IAMOBSERVINGEXAMINED:
            relation = "observing examined";
            break;

        case FicsStyle12::IAMOBSERVINGPLAYED:
            relation = "observing";
            break;

        case FicsStyle12::IAMPLAYINGMYMOVE:
        case FicsStyle12::IAMPLAYINGOPPONENTMOVE:
            relation = "playing";
            break;

        case FicsStyle12::ISOLATEDPOSITION:
            relation = "postion";
            break;
        }

    ui->gameInfoLabel->setText(QString("%1 %2 %3: %4 min + %5 sec").arg(relation).arg(ginfo->LongGameCategory()).arg(ginfo->IsRated() ? "rated" : "unrated").arg(ginfo->TimeMinutes()).arg(ginfo->TimeIncrement()));
    }

void GameBoard::updatePlayerInfo(FicsGameInfo *ginfo)
    {
    if (m_GameOver)
        {
        return;
        }

    if (ui->chessBoardWidget->WhiteOnTop())
        {
        ui->label_top_name->setText(ginfo->WhiteName());
        ui->label_top_colordesc->setText("as white");
        ui->label_top_rating->setText(QString("(%1)").arg(ginfo->WhiteRating()));
        ui->label_bottom_name->setText(ginfo->BlackName());
        ui->label_bottom_colordesc->setText("as black");
        ui->label_bottom_rating->setText(QString("(%1)").arg(ginfo->BlackRating()));
        }
    else
        {
        ui->label_top_name->setText(ginfo->BlackName());
        ui->label_top_colordesc->setText("as black");
        ui->label_top_rating->setText(QString("(%1)").arg(ginfo->BlackRating()));
        ui->label_bottom_name->setText(ginfo->WhiteName());
        ui->label_bottom_colordesc->setText("as white");
        ui->label_bottom_rating->setText(QString("(%1)").arg(ginfo->WhiteRating()));
        }
    }

void GameBoard::setGameOver(FicsBannerInfo *banner_info)
    {
    setGameOver(QString("%1: %2 => %3")
                .arg(ui->gameInfoLabel->text())
                .arg(banner_info->BannerDescription())
                .arg(banner_info->BannerResult()));
    }

void GameBoard::setGameOver(QString reason)
    {
    if (m_GameOver)
        {
        return;
        }

    m_GameOver = true;
    StopClocks();
    setCanClose(GameFlags::CloseAllowed);
    ui->gameInfoLabel->setText(reason);
    }

void GameBoard::updateStrengths()
    {
    QString whitestr = QString("Str: %1").arg(m_PositionData->WhiteMaterial());
    QString blackstr = QString("Str: %1").arg(m_PositionData->BlackMaterial());

    if (ui->chessBoardWidget->WhiteOnTop())
        {
        ui->label_top_material->setText(QString("Str: %1").arg(m_PositionData->WhiteMaterial()));
        ui->label_bottom_material->setText(QString("Str: %1").arg(m_PositionData->BlackMaterial()));
        }
    else
        {
        ui->label_top_material->setText(QString("Str: %1").arg(m_PositionData->BlackMaterial()));
        ui->label_bottom_material->setText(QString("Str: %1").arg(m_PositionData->WhiteMaterial()));
        }
    }

void GameBoard::updateClocks()
    {
    ChessClock *whiteLCD;
    ChessClock *blackLCD;

    if (ui->chessBoardWidget->WhiteOnTop())
        {
        whiteLCD = ui->topPlayerClockLCD;
        blackLCD = ui->bottomPlayerClockLCD;
        }
    else
        {
        whiteLCD = ui->bottomPlayerClockLCD;
        blackLCD = ui->topPlayerClockLCD;
        }

    whiteLCD->setSeconds(m_PositionData->WhiteRemainingTimeSeconds());
    blackLCD->setSeconds(m_PositionData->BlackRemainingTimeSeconds());

    if (m_PositionData->ClockTicking() == false)
        {
        whiteLCD->StopCountDown();
        blackLCD->StopCountDown();
        }
    else
        {
        if (m_PositionData->WhiteToMove())
            {
            whiteLCD->StartCountDown();
            blackLCD->StopCountDown();
            }
        else
            {
            whiteLCD->StopCountDown();
            blackLCD->StartCountDown();
            }
        }
    }

void GameBoard::updateLastMoved()
    {
    if (PositionData()->VerboseCoordinateNotationPreviousMove() == "none")
        {
        return;
        }

    QRegularExpression *foo = new QRegularExpression(R"foo((.)/(..)-(..))foo");
    QRegularExpressionMatch m1 = foo->match(PositionData()->VerboseCoordinateNotationPreviousMove());
    QString from_square, to_square;
    int from_file, from_rank;
    int to_file, to_rank;

    if (m1.hasMatch())
        {
        for (int i = 0; i < previous_highlighted.size(); ++i)
            {
            from_square = previous_highlighted.at(i);
            from_file = from_square[0].unicode() - QChar('a').unicode();
            from_rank = from_square[1].unicode() - QChar('1').unicode();
            ui->chessBoardWidget->setSquareHighlight(from_file, from_rank, false);
            }

        previous_highlighted.clear();
        from_square = m1.captured(2);
        previous_highlighted.append(from_square);
        to_square = m1.captured(3);
        previous_highlighted.append(to_square);
        from_file = from_square[0].unicode() - QChar('a').unicode();
        from_rank = from_square[1].unicode() - QChar('1').unicode();
        ui->chessBoardWidget->setSquareHighlight(from_file, from_rank, true);
        to_file = to_square[0].unicode() - QChar('a').unicode();
        to_rank = to_square[1].unicode() - QChar('1').unicode();
        ui->chessBoardWidget->setSquareHighlight(to_file, to_rank, true);
        }
    }

void GameBoard::updateLag()
    {
    qreal lagsecs = m_PositionData->LagTimeMilliseconds() / 1000.0;
    QString lastmovelag = QString("Lag: %1").arg(lagsecs, 0, 'f', 3);

    if (ui->chessBoardWidget->WhiteOnTop())
        {
        if (m_PositionData->WhiteToMove() == false)
            {
            ui->label_top_lag->setText(lastmovelag);
            }
        else
            {
            ui->label_bottom_lag->setText(lastmovelag);
            }
        }
    else
        {
        if (m_PositionData->WhiteToMove() == false)
            {
            ui->label_bottom_lag->setText(lastmovelag);
            }
        else
            {
            ui->label_top_lag->setText(lastmovelag);
            }
        }
    }


bool GameBoard::IAmPlayingGame(FicsStyle12::GameRelation relation)
    {
    if ((relation == FicsStyle12::GameRelation::IAMPLAYINGMYMOVE)
            || (relation == FicsStyle12::GameRelation::IAMPLAYINGOPPONENTMOVE))
        {
        return true;
        }
    else
        {
        return false;
        }
    }

