/* Copyright (C) 2021 Nature Easy Soft Network Technology Co., LTD
 *
 * This file is part of Zenshot (https://github.com/easysoft/zenshot/).
 *
 * Zenshot is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zenshot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zenshot. If not, see <https://www.gnu.org/licenses/>.
 */

#include "core/handle.h"
#include "core/utils.h"

#include <QPen>
#include <QBrush>
#include <QPoint>

Handle::Handle(Locator *locator)
{
    this->m_locator = locator;
}

Locator *Handle::locator() const
{
    return m_locator;
}

QRect Handle::boundary()
{
    int size = Utils::Handle_Shape_Size;
    QPoint center = m_locator->location();
    QRect rect(center.x()-size/2, center.y()-size/2, size, size);

    return  rect;
}

bool Handle::contain(QPointF point)
{
    QRectF mBoundary = boundary();
    return  mBoundary.contains(point.x(),point.y());
}

void Handle::move(QPoint point)
{
    m_locator->setLocation(point);
}

void Handle::draw(QPainter &painter)
{
    painter.save();

    QPen pen;
    pen.setColor(Utils::Handle_Shape_Border_Color);
    pen.setWidth(Utils::Handle_Shape_Border_Thickness);

    QBrush brush;
    brush.setColor(Utils::Handle_Shape_Fill_Color);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);

    QRectF mBoundary = boundary();

    painter.drawEllipse(mBoundary);

    painter.restore();
}

void Handle::setCursor(QWidget *targetUI)
{
    targetUI->setCursor(Qt::SizeAllCursor);
}

