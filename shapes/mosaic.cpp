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

#include "mosaic.h"
#include "screen/workspace.h"

#include <QImage>

Mosaic::Mosaic(Workspace *workspace):PointsShape(workspace)
{
    loadProps();
}

QString Mosaic::type()
{
    return Utils::forMosaicKey();
}

QRect Mosaic::boundary()
{
    QVector<QRect> rects = getRects();

    int minX = m_points[0].x();
    int maxX = m_points[0].x();
    int minY = m_points[0].y();
    int maxY = m_points[0].y();

    foreach(QRect rect, rects)
    {
        minX = minX < rect.x() ? minX : rect.x();
        maxX = maxX > (rect.x()+rect.width()) ? maxX : (rect.x()+rect.width());

        minY = minY < rect.y() ? minY : rect.y();
        maxY = maxY > (rect.y()+rect.height()) ? maxY : (rect.y()+rect.height());
    }

    return QRect(minX, minY, maxX-minX, maxY-minY);
}

QVector<QRect> Mosaic::getRects()
{
    QVector<QRect> rects;

    QRect areaRect = m_workspace->areaBoundary();

    for(QPoint point:m_points)
    {
        bool hasInclude = false;
        for(QRect existRect:rects)
        {
            if(existRect.contains(point) == true)
            {
                hasInclude = true;
                break;
            }
        }
        if(hasInclude == true)
            continue;

        int rowIndex = (point.y()-areaRect.y())/m_lineWidth;
        int colInex = (point.x()-areaRect.x())/m_lineWidth;

        double x = areaRect.x() + colInex * m_lineWidth;
        double y = areaRect.y() + rowIndex * m_lineWidth;

        QRect rect(x,y,m_lineWidth,m_lineWidth);
        rects.append(rect);
    }

    return rects;
}

QVector<Handle *> Mosaic::handles()
{
    QVector<Handle *> handle;
    return  handle;
}

void Mosaic::draw(QPainter &painter)
{
    painter.save();

    QImage bgImg = m_workspace->pixmap().toImage();

    QVector<QRect> rects = getRects();
    for(QRectF rect:rects)
    {

        QColor lefttop = bgImg.pixel(rect.x(),rect.y());
        QColor righttop = bgImg.pixel(rect.x()+rect.width(),rect.y());
        QColor leftbottom = bgImg.pixel(rect.x(),rect.y()+rect.height());
        QColor rightbottom = bgImg.pixel(rect.x()+rect.width(),rect.y()+rect.height());
        QColor center = bgImg.pixel(rect.x()+rect.width()/2,rect.y()+rect.height()/2);

        int r = (lefttop.red() + righttop.red() + rightbottom.red() + leftbottom.red() + center.red())/5;
        int g = (lefttop.green() + righttop.green() + rightbottom.green() + leftbottom.green() + center.green())/5;
        int b = (lefttop.blue() + righttop.blue() + rightbottom.blue() + leftbottom.blue() + center.blue())/5;

        QBrush brush(QColor(r,g,b),Qt::SolidPattern);
        painter.fillRect(rect,brush);
    }

    painter.restore();

    /* 下面的代码屏蔽掉，马赛克不支持绘制选中边框线
    if(m_selected == true)
    {
        drawAntIndicator(painter,boundary());
    }
    */
}

bool Mosaic::contain(QPoint point)
{
    return false;

    /* 下面的代码注释掉，屏蔽掉马赛克的选中功能
    QVector<QRect> rects = getRects();
    for(QRectF rect:rects)
    {
        if(rect.contains(point) == true)
            return true;
    }

    return false;
    */
}

void Mosaic::loadPropsImpl(Store *store)
{
    m_lineWidth = store->read(Utils::forMosaicKey(),Utils::MosaicSizeName(),Utils::MosaicSizeDefault()).toInt();
}

void Mosaic::savePropsImpl(Store *store)
{
    store->write(Utils::forMosaicKey(),Utils::MosaicSizeName(),m_lineWidth);
}
