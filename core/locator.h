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

#ifndef LOCATOR_H
#define LOCATOR_H

#include <QPoint>
#include <QRect>

/**
 * @class : Locator
 * @brief : 定位器基类定义
 * @note  : 用于定位图形中的关键点
 */
class Locator
{
public:
    explicit Locator();

    /**
     * @brief 获取对应的坐标点
     * @return 坐标值
     */
    virtual QPoint location() = 0;

    /**
     * @brief 设置对应点的坐标
     * @param point
     */
    virtual void setLocation(QPoint point) = 0;
};

#endif // LOCATOR_H
