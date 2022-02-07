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

#ifndef AREAHANDLE_H
#define AREAHANDLE_H

#include "core/handle.h"
#include "screen/shotarea/arealocator.h"
#include "core/utils.h"

/**
 * @class : AreaHandle
 * @brief : 截图区域控制手柄类定义
 * @note  : 图形选中后出现，鼠标拖拽控制手柄可以修改图形
 */
class AreaHandle : public Handle
{
public:
    explicit AreaHandle(AreaLocator *locator);

    void draw(QPainter &painter);
    QRect boundary();

    void flipAnchorX();
    void flipAnchorY();
    void setCursor(QWidget *targetUI);

private:
    Utils::RectAnchor m_anchor;
};

#endif // AREAHANDLE_H
