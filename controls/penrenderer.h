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

#ifndef PENRENDERER_H
#define PENRENDERER_H

#include <QWidget>
#include <QColor>

class PenRenderer
{
public: 
    PenRenderer(QWidget *widget,Qt::PenStyle penStyle, int marginLeft,int marginRight);

    void draw();

    Qt::PenStyle penStyle() const;
    void setPenStyle(const Qt::PenStyle &penStyle);

private:
    QWidget *m_widget;

    int m_marginLeft;
    int m_marginRight;

    int m_lineWidth;
    QColor m_lineColor;
    Qt::PenStyle m_penStyle;


};

#endif // PENRENDERER_H
