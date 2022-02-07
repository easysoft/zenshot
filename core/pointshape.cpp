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

#include "pointshape.h"
#include "locators/pointlocator.h"
#include "core/handle.h"
#include "core/utils.h"

#include <QPolygon>

PointsShape::PointsShape(Workspace *workspace):Shape(workspace)
{

}

int PointsShape::count()
{
    return m_points.count();
}

QPoint PointsShape::pointAt(int index)
{
    return m_points.at(index);
}

void PointsShape::setPointAt(QPoint point, int index)
{
    m_points[index] = point;
}

void PointsShape::removePointAt(int index)
{
    m_points.removeAt(index);
}

void PointsShape::addPoint(QPoint point)
{
    m_points.append(point);
}

QRect PointsShape::boundary()
{
    int minX = m_points[0].x();
    int maxX = m_points[0].x();
    int minY = m_points[0].y();
    int maxY = m_points[0].y();

    foreach(QPointF p, m_points)
    {
        minX = minX < p.x() ? minX : p.x();
        maxX = maxX > p.x() ? maxX :p.x();

        minY = minY < p.y() ? minY : p.y();
        maxY = maxY > p.y() ? maxY : p.y();
    }

    return QRect(minX, minY, maxX-minX, maxY-minY);
}

QVector<Handle *> PointsShape::handles()
{
    QVector<Handle*> results;

    int mCount = count();
    for(int i=0;i<mCount;i++)
    {
        PointLocator *locator = new PointLocator(this,i);
        Handle *handle = new Handle(locator);
        results.append(handle);
    }

    return  results;
}

bool PointsShape::contain(QPoint point)
{
    int mCount = count();
    for(int i=1;i<mCount;i++)
    {
        QPoint p1 = m_points[i-1];
        QPoint p2 = m_points[i];

        //下面的注释掉，否则宽线条两端会产生问题，还有自由曲线的选择也会有问题
        //if(Utils::contains(p1,p2,point) == false)
        //{
        //    continue;
        //}

        if(Utils::distance(p1,p2,point) <= m_lineWidth/2+Utils::Hit_Snap)
        {
            return true;
        }
    }

    return false;
}

void PointsShape::move(QPoint offsetPoint)
{
    int pointCount = count();
    for(int i=0;i<pointCount;i++)
    {
        QPoint tmp = m_points[i];
        tmp.setX(tmp.x() + offsetPoint.x());
        tmp.setY(tmp.y() + offsetPoint.y());

        m_points[i] = tmp;
    }
}

void PointsShape::draw(QPainter &painter)
{
    painter.save();

    QPen pen;
    pen.setWidth(m_lineWidth);
    pen.setColor(m_lineColor);
    pen.setStyle(m_lineStyle);

    painter.setPen(pen);

    QPolygon polygon(m_points);
    painter.drawPolyline(polygon);

    painter.restore();
}







