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

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPointer>
#include <QPaintEvent>
#include <QObject>
#include <QtCore>
#include <QPoint>
#include <QPainter>
#include <QString>
#include <QIcon>
#include <QMap>

#include "chesssquare.h"
#include "gameflags.h"

class ChessBoard : public QWidget
    {
        Q_OBJECT
        Q_PROPERTY(QColor DarkSquareColor READ DarkSquareColor WRITE setDarkSquareColor)
        Q_PROPERTY(QColor LightSquareColor READ LightSquareColor WRITE setLightSquareColor)
        Q_PROPERTY(QPen MoveHightlightPen READ MoveHightlightPen WRITE setMoveHightlightPen)
        Q_PROPERTY(int Files READ Files WRITE setFiles)
        Q_PROPERTY(int Ranks READ Ranks WRITE setRanks)
        Q_PROPERTY(bool WhiteOnTop READ WhiteOnTop WRITE setWhiteOnTop)
        //Q_PROPERTY(bool AcceptMouseInput READ AcceptMouseInput WRITE setAcceptMouseInput)
        Q_PROPERTY(GameFlags::AcceptMouse AcceptMouseInput READ AcceptMouseInput WRITE setAcceptMouseInput)
        Q_PROPERTY(bool IsMyMove READ IsMyMove WRITE setIsMyMove)
        //Q_PROPERTY(QColor DarkSquareHighlightColor READ DarkSquareHighlightColor WRITE setDarkSquareHighlightColor)

    private:
        QMap<GameFlags::PieceType, QIcon> m_chesspieces;
        QVector<QVector<ChessSquare *>> m_chessgrid;
        QSizeF m_SquareSize;
        QPointF m_Offset;

        ChessSquare *itemInMotion;                  // Square that has piece movement
        int itemOrigFile;                           // Original file before movement
        int itemOrigRank;                           // Original rank before movement
        QPointF itemOriginalPosition;               // Original top left corner of icon before movement

        void moveIconTo(QPointF pos, bool center);
        void resetChessBoard();
        void drawCheckerBoard(QPainter *p);
        void drawSquare(QPainter *p, int file, int rank);
        void drawPieces(QPainter *p);
        void drawPiece(QPainter *p, int file, int rank);
        void drawSquareHighLights(QPainter *p);
        bool getFileRankFromPos(int &file, int &rank, QPointF mousePoint);
        void updateChessBoardColors();
        void updateChessBoardGeometry();
        void updateChessSquareGeometry(ChessSquare *sq, int file, int rank);

        QColor m_DarkSquareColor;
        QColor m_LightSquareColor;
        int m_Files;
        int m_Ranks;
        bool m_WhiteOnTop;
        //bool m_AcceptMouseInput;

        GameFlags::AcceptMouse m_AcceptMouseInput;

        bool m_IsMyMove;

        QPen m_MoveHightlightPen;
        int movehighlightPenWidth;

    public:
        explicit ChessBoard(QWidget *parent = nullptr);

        void setChessPieceIcon(GameFlags::PieceType ptype, const QIcon &icon);
        GameFlags::PieceType putPiece(GameFlags::PieceType ptype, int file, int rank, bool delay);
        void RevertPutPiece(GameFlags::PieceType source_piece, int source_file, int source_rank, GameFlags::PieceType target_piece, int target_file, int target_rank);

        void putPosition(QVector<QVector<GameFlags::PieceType>> position);
        QColor DarkSquareColor() const;
        QColor LightSquareColor() const;
        int Files() const;
        int Ranks() const;
        bool WhiteOnTop() const;
        bool IsPieceMoveAllowed(int file, int rank);


        GameFlags::AcceptMouse AcceptMouseInput() const;

        bool IsMyMove() const;

        QPen MoveHightlightPen() const;

    signals:
        void signalChessMove(GameFlags::PieceType fromPiece, int fromFile, int fromRank, GameFlags::PieceType toPiece, int toFile, int toRank);

    public slots:

        // QWidget interface
        void setDarkSquareColor(QColor DarkSquareColor);
        void setLightSquareColor(QColor LightSquareColor);
        void setFiles(int Files);
        void setRanks(int Ranks);
        void setWhiteOnTop(bool WhiteOnTop);
        //void setAcceptMouseInput(bool AcceptMouseInput);

        void setAcceptMouseInput(GameFlags::AcceptMouse AcceptMouseInput);
        void setSquareHighlight(int file, int rank, bool highlight_on);

        void setIsMyMove(bool IsMyMove);

        void setMoveHightlightPen(QPen MoveHightlightPen);

    protected:
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void paintEvent(QPaintEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;
    };

#endif // CHESSBOARD_H
