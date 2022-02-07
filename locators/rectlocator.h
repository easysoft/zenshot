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

#ifndef RECTLOCATOR_H
#define RECTLOCATOR_H

#include <QPoint>

#include "core/locator.h"
#include "core/rectshape.h"
#include "core/utils.h"

/**
 * @class : RectLocator
 * @brief : 基于矩形区域的定位
 * @note  : 矩形四个角和四条边的中间共8个点坐标的定位
 */
class RectLocator : public Locator
{
public:
    explicit RectLocator(RectShape* shape,Utils::RectAnchor anchor);

    Utils::RectAnchor anchor();
    void setAnchor(Utils::RectAnchor value);

    QPoint location();
    void setLocation(QPoint point);

private:
    Utils::RectAnchor m_anchor;
    RectShape* m_shape;
};

#endif // RECTLOCATOR_H
