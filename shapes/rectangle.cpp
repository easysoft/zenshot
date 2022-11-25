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

#include "rectangle.h"
#include "screen/workspace.h"

#include "spdlogwrapper.hpp"

#include <QPainterPath>

Rectangle::Rectangle(Workspace *workspace):RectShape(workspace)
{
    loadProps();
}

QString Rectangle::type()
{
    return Utils::forRectKey();
}

bool Rectangle::contain(QPoint point)
{
    //获取矩形区域(边框线完全在矩形区域内)
    QRect mBoundary = boundary();

    //计算拾取区域外侧的矩形区域（会向外扩展一定的距离）
    int mBigExtend = Utils::Hit_Snap;
    QRect mBig = mBoundary.adjusted(-mBigExtend,-mBigExtend,mBigExtend,mBigExtend);

    //计算拾取区域内测的矩形区域（会向内扩展一定的距离）
    int mSmallExtend = m_lineWidth + Utils::Hit_Snap;
    QRect mSmall = mBoundary.adjusted(mSmallExtend,mSmallExtend,-mSmallExtend,-mSmallExtend);

    //绘制粗线条窄矩形框的处理(中间被图形挤满了，没有空白)
    if(mBoundary.width() < m_lineWidth*2 || mBoundary.height() < m_lineWidth*2)
    {
        return mBig.contains(point);
    }

    //判断外矩形框（图形多的时候可以一定程度优化性能，这里貌似没太必要）
    if(mBig.contains(point) == false)
    {
        return false;
    }

    QPainterPath path;
    path.addRect(mBig);
    path.addRect(mSmall);

    return path.contains(point);
}

void Rectangle::draw(QPainter &painter)
{
    painter.save();

    QRect mBoundary = boundary();
    QRect drawRect = mBoundary.adjusted(m_lineWidth/2,m_lineWidth/2,-m_lineWidth/2,-m_lineWidth/2);

    //下面的代码防止在绘制粗矩形框的时候，绘制出的图形跑出矩形区域外
    if(m_lineWidth >4 && (mBoundary.width() < m_lineWidth*2 || mBoundary.height() < m_lineWidth*2))
    {
        QPainterPath selfClipPath;
        selfClipPath.addRect(m_boundary);

        QPainterPath globalClipPath;
        globalClipPath.addRect(m_workspace->areaBoundary());

        QPainterPath clipPath = globalClipPath.intersected(selfClipPath);

        painter.setClipPath(clipPath);
    }

    QPen pen;
    pen.setWidth(m_lineWidth);
    pen.setColor(m_lineColor);
    pen.setStyle(m_lineStyle);
    pen.setJoinStyle(Qt::MiterJoin);

    painter.setPen(pen);
    painter.drawRect(drawRect);

    painter.restore();

    if(m_selected == true)
    {
        drawAntIndicator(painter,mBoundary);
    }
}

void Rectangle::loadPropsImpl(Store *store)
{
    m_lineWidth = store->read(Utils::forRectKey(),Utils::RectWidthName(),Utils::RectWidthDefault()).toInt();
    m_lineColor = store->readColor(Utils::forRectKey(),Utils::RectColorName(),Utils::RectColorDefault());
    m_lineStyle = store->readPenStyle(Utils::forRectKey(),Utils::RectStyleName(),Utils::RectStyleDefault());

    L_DEBUG("{0} @ {1}: m_lineWidth = {2}, m_lineStyle = {3}", __FUNCTION__, __LINE__, m_lineWidth, m_lineStyle);
}

void Rectangle::savePropsImpl(Store *store)
{
    store->write(Utils::forRectKey(),Utils::RectWidthName(),m_lineWidth);
    store->writeColor(Utils::forRectKey(),Utils::RectColorName(),m_lineColor);
    store->writePenStyle(Utils::forRectKey(),Utils::RectStyleName(),m_lineStyle);

    L_DEBUG("{0} @ {1}: m_lineWidth = {2}, m_lineStyle = {3}", __FUNCTION__, __LINE__, m_lineWidth, m_lineStyle);
}
