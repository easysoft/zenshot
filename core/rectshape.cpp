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

#include "rectshape.h"
#include "handles/rectshapehandle.h"
#include "locators/rectlocator.h"
#include "core/utils.h"
#include "screen/workspace.h"

RectShape::RectShape(Workspace *workspace):Shape(workspace)
{
    m_lineWidth = 2;
    m_lineColor = QColor(251,56,56);
    m_lineStyle = Qt::SolidLine;
}

void RectShape::setBoundary(QRect rect)
{
    m_boundary.setRect(rect.x(),rect.y(),rect.width(),rect.height());
}

QRect RectShape::boundary()
{
    return  m_boundary;
}

QVector<Handle*> RectShape::handles()
{
    QVector<Handle*> results;


    RectLocator *topLeft = new RectLocator(this,Utils::RECT_TOP_LEFT);
    RectShapeHandle *topLeftHandle = new RectShapeHandle(topLeft);
    results.append(topLeftHandle);

    RectLocator *topMiddle = new RectLocator(this,Utils::RECT_TOP_MIDDLE);
    RectShapeHandle *topMiddleHandle = new RectShapeHandle(topMiddle);
    results.append(topMiddleHandle);

    RectLocator *topRight = new RectLocator(this,Utils::RECT_TOP_RIGHT);
    RectShapeHandle *topRightHandle = new RectShapeHandle(topRight);
    results.append(topRightHandle);

    RectLocator *leftMiddle = new RectLocator(this,Utils::RECT_LEFT_MIDDLE);
    RectShapeHandle *leftMiddleHandle = new RectShapeHandle(leftMiddle);
    results.append(leftMiddleHandle);

    RectLocator *rightMiddle = new RectLocator(this,Utils::RECT_RIGHT_MIDDLE);
    RectShapeHandle *rightMiddleHandle = new RectShapeHandle(rightMiddle);
    results.append(rightMiddleHandle);


    RectLocator *bottomLeft = new RectLocator(this,Utils::RECT_BOTTOM_LEFT);
    RectShapeHandle *bottomLeftHandle = new RectShapeHandle(bottomLeft);
    results.append(bottomLeftHandle);

    RectLocator *bottomMiddle = new RectLocator(this,Utils::RECT_BOTTOM_MIDDLE);
    RectShapeHandle *bottomMiddleHandle = new RectShapeHandle(bottomMiddle);
    results.append(bottomMiddleHandle);

    RectLocator *bottomRight = new RectLocator(this,Utils::RECT_BOTTOM_RIGHT);
    RectShapeHandle *bottomRightHandle = new RectShapeHandle(bottomRight);
    results.append(bottomRightHandle);


    return  results;
}

bool RectShape::contain(QPoint point)
{
    QRectF rect = boundary();
    return rect.contains(point);
}

void RectShape::move(QPoint offsetPoint)
{
    m_boundary.setRect(m_boundary.x()+offsetPoint.x(),m_boundary.y()+offsetPoint.y(),m_boundary.width(),m_boundary.height());
}

void RectShape::draw(QPainter &painter)
{
    painter.save();

    QRect mBoundary = boundary();

    QPen pen;
    pen.setWidth(m_lineWidth);
    pen.setColor(m_lineColor);
    pen.setStyle(m_lineStyle);
    pen.setJoinStyle(Qt::MiterJoin);

    painter.setPen(pen);
    painter.drawRect(mBoundary);

    painter.restore();

    if(m_selected == true)
    {
        drawAntIndicator(painter,mBoundary);
    }
}

int RectShape::lineWidth() const
{
    return m_lineWidth;
}



