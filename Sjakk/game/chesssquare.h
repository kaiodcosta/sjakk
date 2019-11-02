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

#ifndef CHESSSQUARE_H
#define CHESSSQUARE_H

#include <QObject>
#include <QRect>
#include <QColor>
#include <QIcon>
#include <QPointF>
#include <QSizeF>
#include <QPen>
#include "gameflags.h"

class ChessSquare : public QObject
    {
        Q_OBJECT
    public:
        explicit ChessSquare(QObject *parent = nullptr);
        QPen borderPen;
        QColor fillColor;
        QBrush fillBrush;
        QRectF fillArea;
        QIcon pieceIcon;
        QRectF pieceIconFillArea;
        QPen highlightPen;
        GameFlags::PieceType pieceType;
        QRectF highlightfillArea;
        QPen highlightborderPen;
        QBrush highlightfillBrush;
        int highlightborderWidth;

    signals:

    public slots:
    };

#endif // CHESSSQUARE_H
