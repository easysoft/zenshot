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

#ifndef POINTLOCATOR_H
#define POINTLOCATOR_H

#include "core/locator.h"
#include "core/pointshape.h"

/**
 * @class : PointLocator
 * @brief : 基于索引的点定位器
 * @note  : 提供基于PointsShape的图形定位功能
 */
class PointLocator : public Locator
{
public:
    explicit PointLocator(PointsShape *shape,int index);

    void setLocation(QPoint point);
    QPoint location();

private:
    int m_index;
    PointsShape *m_shape;
};

#endif // POINTLOCATOR_H
