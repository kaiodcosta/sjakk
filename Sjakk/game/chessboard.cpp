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

#include "chessboard.h"

void ChessBoard::moveIconTo(QPointF pos, bool center)
    {
    if (center)
        this->itemInMotion->pieceIconFillArea.moveCenter(pos);
    else
        this->itemInMotion->pieceIconFillArea.moveTo(pos);

    this->update();
    }

void ChessBoard::resetChessBoard()
    {
    m_chessgrid.clear();
    m_chessgrid.resize(this->Files());

    for (int i = 0; i < this->Files(); i++)
        m_chessgrid[i].resize(this->Ranks());

    for (int file = 0; file < this->Files(); file++)
        {
        for (int rank = 0; rank < this->Ranks(); rank++)
            {
            ChessSquare *sq = new ChessSquare(this);
            m_chessgrid[file][rank] = sq;
            }
        }
    }

void ChessBoard::drawCheckerBoard(QPainter *p)
    {
    for (int file = 0; file < this->Files(); ++file)
        {
        for (int rank = 0; rank < this->Ranks(); ++rank)
            this->drawSquare(p, file, rank);
        }
    }

void ChessBoard::drawSquare(QPainter *p, int file, int rank)
    {
    ChessSquare *sq = m_chessgrid[file][rank];
    p->save();
    p->setPen(sq->borderPen);
    p->setBrush(sq->fillBrush);
    p->drawRect(sq->fillArea);
    p->restore();
    }

void ChessBoard::drawPieces(QPainter *p)
    {
    for (int file = 0; file < this->Files(); ++file)
        {
        for (int rank = 0; rank < this->Ranks(); ++rank)
            this->drawPiece(p, file, rank);
        }
    }

void ChessBoard::drawPiece(QPainter *p, int file, int rank)
    {
    ChessSquare *sq = m_chessgrid[file][rank];

    if (!sq->pieceIcon.isNull())
        sq->pieceIcon.paint(p, sq->pieceIconFillArea.toRect(), Qt::AlignCenter);
    }

void ChessBoard::drawSquareHighLights(QPainter *p)
    {
    p->save();

    for (int f = 0 ; f < Files(); f++)
        for (int r = 0; r < Ranks(); r++)
            {
            ChessSquare *sq = m_chessgrid[f][r];
            p->setPen(sq->highlightPen);
            p->setBrush(sq->highlightfillBrush);
            p->drawRect(sq->highlightfillArea);
            }

    p->restore();
    }

bool ChessBoard::getFileRankFromPos(int &file, int &rank, QPointF mousePoint)
    {
    for (int f = 0; f < this->Files(); f++)
        {
        for (int r = 0; r < this->Ranks(); r++)
            {
            if (m_chessgrid[f][r]->fillArea.contains(mousePoint))
                {
                file = f;
                rank = r;
                return true;
                }
            }
        }

    return false;
    }

void ChessBoard::updateChessBoardColors()
    {
    for (int file = 0; file < this->Files(); file++)
        {
        for (int rank = 0; rank < this->Ranks(); rank++)
            {
            ChessSquare *sq = m_chessgrid[file][rank];
            //sq->fillColor = QColor((file + rank) % 2 ? this->LightSquareColor() : this->DarkSquareColor());
            sq->fillBrush = QBrush(QColor((file + rank) % 2 ? this->LightSquareColor() : this->DarkSquareColor()));
            sq->borderPen = QPen(Qt::PenStyle::NoPen);
            sq->highlightPen = QPen(Qt::PenStyle::NoPen);
            }
        }
    }

void ChessBoard::updateChessBoardGeometry()
    {
    qreal w, h, board_size;
    w = this->width();
    h = this->height();
    board_size = (h < w) ? h : w;
    this->m_SquareSize = QSizeF(board_size / static_cast<qreal>(this->Files()), board_size / static_cast<qreal>(this->Ranks()));

    if (h < w)
        {
        m_Offset.setY(0);
        m_Offset.setX((w / 2) - (this->m_SquareSize.height() * 4));
        }
    else
        {
        m_Offset.setY((h / 2) - (this->m_SquareSize.width() * 4));
        m_Offset.setX(0);
        }

    for (int file = 0; file < this->Files(); file++)
        {
        for (int rank = 0; rank < this->Ranks(); rank++)
            {
            ChessSquare *sq = m_chessgrid[file][rank];
            updateChessSquareGeometry(sq, file, rank);
            }
        }
    }

void ChessBoard::updateChessSquareGeometry(ChessSquare *sq, int file, int rank)
    {
    int relrank;
    int relfile;

    if (WhiteOnTop())
        {
        relrank = rank;
        relfile = this->Files() - 1 - file;
        }
    else
        {
        relrank = this->Ranks() - 1 - rank;
        relfile = file;
        }

    QPointF topLeft(relfile * m_SquareSize.width(), relrank * m_SquareSize.height());
    topLeft += m_Offset;
    sq->fillArea = QRectF(topLeft, m_SquareSize);
    sq->pieceIconFillArea = QRectF(sq->fillArea);
    sq->highlightfillArea = QRectF(sq->fillArea);
    sq->highlightfillArea -= QMargins(2, 2, 2, 2);
    sq->highlightfillArea.setTop(sq->fillArea.top() + 2);
    sq->highlightfillArea.setLeft(sq->fillArea.left() + 2);
    }

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
    {
    this->setFiles(8);
    this->setRanks(8);
    this->setWhiteOnTop(false);
    this->setAcceptMouseInput(GameFlags::AcceptMouse::AcceptNone);
    this->setDarkSquareColor(QColor(85, 107, 47, 255));   // Dark Olive
    this->setLightSquareColor(QColor(245, 222, 179, 255)); // Wheat
    setMoveHightlightPen(QPen(QBrush(Qt::blue), 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    movehighlightPenWidth = 2;
    }

void ChessBoard::setChessPieceIcon(GameFlags::PieceType ptype, const QIcon &icon)
    {
    m_chesspieces.insert(ptype, icon);
    this->update();
    }

GameFlags::PieceType ChessBoard::putPiece(GameFlags::PieceType ptype, int file, int rank, bool delay)
    {
    ChessSquare *sq = m_chessgrid[file][rank];
    GameFlags::PieceType original_piece = sq->pieceType;
    sq->pieceType = ptype;

    if (sq->pieceType != GameFlags::PieceType::NoPiece)
        sq->pieceIcon = m_chesspieces.value(ptype, QIcon());
    else
        sq->pieceIcon = QIcon();

    if (!delay)
        update();

    return original_piece;
    }

void ChessBoard::RevertPutPiece(GameFlags::PieceType source_piece, int source_file, int source_rank, GameFlags::PieceType target_piece, int target_file, int target_rank)
    {
    putPiece(source_piece, source_file, source_rank, false);
    putPiece(target_piece, target_file, target_rank, false);
    }

void ChessBoard::putPosition(QVector<QVector<GameFlags::PieceType> > position)
    {
    GameFlags::PieceType target, current;

    for (int f = 0; f < 8; f++)
        {
        for (int r = 0; r < 8; r++)
            {
            target = position[f][r];
            current = m_chessgrid[f][r]->pieceType;

            if (current != target)
                putPiece(target, f, r, true);
            }
        }

    update();
    }

QColor ChessBoard::DarkSquareColor() const
    {
    return m_DarkSquareColor;
    }

QColor ChessBoard::LightSquareColor() const
    {
    return m_LightSquareColor;
    }

int ChessBoard::Files() const
    {
    return m_Files;
    }

int ChessBoard::Ranks() const
    {
    return m_Ranks;
    }

bool ChessBoard::WhiteOnTop() const
    {
    return m_WhiteOnTop;
    }

GameFlags::AcceptMouse ChessBoard::AcceptMouseInput() const
    {
    return m_AcceptMouseInput;
    }

bool ChessBoard::IsMyMove() const
    {
    return m_IsMyMove;
    }

QPen ChessBoard::MoveHightlightPen() const
    {
    return m_MoveHightlightPen;
    }

void ChessBoard::setDarkSquareColor(QColor DarkSquareColor)
    {
    if (this->m_DarkSquareColor == DarkSquareColor)
        return;

    this->m_DarkSquareColor = DarkSquareColor;
    this->updateChessBoardColors();
    }

void ChessBoard::setLightSquareColor(QColor LightSquareColor)
    {
    if (this->m_LightSquareColor == LightSquareColor)
        return;

    this->m_LightSquareColor = LightSquareColor;
    this->updateChessBoardColors();
    }

void ChessBoard::setFiles(int Files)
    {
    if (Files <= 0)
        return;

    if (m_Files == Files)
        return;

    m_Files = Files;

    if (m_Ranks <= 0)
        return;

    this->resetChessBoard();
    this->updateChessBoardColors();
    this->updateChessBoardGeometry();
    this->update();
    }

void ChessBoard::setRanks(int Ranks)
    {
    if (Ranks <= 0)
        return;

    if (m_Ranks == Ranks)
        return;

    m_Ranks = Ranks;

    if (m_Files <= 0)
        return;

    this->resetChessBoard();
    this->updateChessBoardColors();
    this->updateChessBoardGeometry();
    this->update();
    }

void ChessBoard::setWhiteOnTop(bool WhiteOnTop)
    {
    if (this->m_WhiteOnTop == WhiteOnTop)
        return;

    this->m_WhiteOnTop = WhiteOnTop;
    this->updateChessBoardGeometry();
    this->update();
    }

void ChessBoard::setAcceptMouseInput(GameFlags::AcceptMouse AcceptMouseInput)
    {
    m_AcceptMouseInput = AcceptMouseInput;
    }

void ChessBoard::setSquareHighlight(int file, int rank, bool highlight_on)
    {
    ChessSquare *sq = m_chessgrid[file][rank];

    if (highlight_on)
        {
        sq->highlightPen = MoveHightlightPen();
        sq->highlightfillBrush = QBrush(Qt::BrushStyle::NoBrush);
        }
    else
        {
        sq->highlightPen = QPen(Qt::PenStyle::NoPen);
        sq->highlightfillBrush = QBrush(Qt::BrushStyle::NoBrush);
        }

    this->update();
    }

void ChessBoard::setIsMyMove(bool IsMyMove)
    {
    m_IsMyMove = IsMyMove;
    }

void ChessBoard::setMoveHightlightPen(QPen MoveHightlightPen)
    {
    m_MoveHightlightPen = MoveHightlightPen;
    }

void ChessBoard::mousePressEvent(QMouseEvent *event)
    {
    int file, rank;

    if (getFileRankFromPos(file, rank, event->localPos()))
        {
        if (IsPieceMoveAllowed(file, rank) == false) return;

        this->itemInMotion = m_chessgrid[file][rank];
        this->itemOriginalPosition = this->itemInMotion->fillArea.topLeft();
        this->itemOrigFile = file;
        this->itemOrigRank = rank;
        }
    else
        this->itemInMotion = nullptr;
    }

bool ChessBoard::IsPieceMoveAllowed(int file, int rank)
    {
    GameFlags::PieceType piece = m_chessgrid[file][rank]->pieceType;

    switch (AcceptMouseInput())
        {
        case GameFlags::AcceptMouse::AcceptAny:
            return true;

        case GameFlags::AcceptMouse::AcceptWhiteInput:
            if (GameFlags::ConvertToColor(piece) == GameFlags::PlayerColor::White) return true;
            else return false;

        case GameFlags::AcceptMouse::AcceptBlackInput:
            if (GameFlags::ConvertToColor(piece) == GameFlags::PlayerColor::Black) return true;
            else return false;

        case GameFlags::AcceptMouse::AcceptNone:
            return false;
        }

    return false;
    }

void ChessBoard::mouseReleaseEvent(QMouseEvent *event)
    {
    int file, rank;

    if (getFileRankFromPos(file, rank, event->localPos()))
        {
        if (this->itemInMotion)
            {
            if (
                ((itemOrigFile == file) && (itemOrigRank == rank)) ||
                (!IsMyMove())
            )
                moveIconTo(itemOriginalPosition, false);
            else
                {
                moveIconTo(itemOriginalPosition, false);
                GameFlags::PieceType ptype = this->itemInMotion->pieceType;
                GameFlags::PieceType source_piece = putPiece(GameFlags::NoPiece, this->itemOrigFile, this->itemOrigRank, false);
                GameFlags::PieceType target_piece = putPiece(ptype, file, rank, false);
                emit signalChessMove(source_piece, itemOrigFile, itemOrigRank, target_piece, file, rank);
                }
            }
        }

    this->itemInMotion = nullptr;
    }

void ChessBoard::mouseMoveEvent(QMouseEvent *event)
    {
    if (AcceptMouseInput() == GameFlags::AcceptMouse::AcceptNone)
        return;

    if (this->itemInMotion)
        this->moveIconTo(event->localPos(), true);
    }

void ChessBoard::paintEvent(QPaintEvent *event)
    {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.save();
    this->drawCheckerBoard(&painter);
    this->drawPieces(&painter);
    this->drawSquareHighLights(&painter);
    painter.restore();
    event->accept();
    }

void ChessBoard::resizeEvent(QResizeEvent *event)
    {
    this->updateChessBoardGeometry();
    event->accept();
    }
