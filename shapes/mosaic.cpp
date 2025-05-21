/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
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
