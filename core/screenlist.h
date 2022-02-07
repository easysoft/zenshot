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

#ifndef SCREENLIST_H
#define SCREENLIST_H

#include <QPainter>
#include <QRect>

#include "core/screeninfo.h"

/**
 * @class : ScreenList
 * @brief : 屏幕列表集合
 * @note  : 屏幕列表集合基本功能
 */
class ScreenList
{
public:
    ScreenList(QList<ScreenInfo> list);

    QRect allBoundary(bool isGlobal=false) const;
    QPixmap allPixMap() const;

    QRect boundaryAt(int screenIndex,bool isGlobal=false);
    QScreen *screenAt(int screenIndex);
    QPixmap pixmapAt(int screenIndex);

    int indexAtMouse();
    QRect toLocal(QRect rect);
    float scale();

    void draw(QPainter &painter);

private:
    QRect m_allBoundary;
    QPixmap m_allPixMap;
    QList<ScreenInfo> m_List;

    void initParams();
};

#endif // SCREENLIST_H
