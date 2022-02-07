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

#ifndef RECTSHAPE_H
#define RECTSHAPE_H

#include <QRect>
#include "core/shape.h"

/**
 * @class : RectShape
 * @brief : 由矩形构成的图形基类
 * @note  : 提供矩形，椭圆图形的基本功能
 */
class RectShape : public Shape
{
public:
    explicit RectShape(Workspace *m_workspace);

    /**
     * @brief 设置矩形
     * @param rect 目标矩形
     */
    void setBoundary(QRect rect);

    /**
     * @brief 获取矩形线宽
     * @return
     */
    int lineWidth() const;

    QRect boundary();
    QVector<Handle*> handles();
    bool contain(QPoint point);
    void move(QPoint offsetPoint);
    void draw(QPainter &painter);

protected:
    QRect m_boundary;            //矩形区域

    int m_lineWidth;             //线的宽度
    QColor m_lineColor;          //线的颜色
    Qt::PenStyle m_lineStyle;    //线条样式
};

#endif // RECTSHAPE_H
