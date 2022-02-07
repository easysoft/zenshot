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

#ifndef MOVETOOL_H
#define MOVETOOL_H

#include <QPoint>

#include "core/tool.h"
#include "core/shape.h"

/**
 * @class : MoveTool
 * @brief : 移动工具类定义
 * @note  : 提供移动图形功能
 */
class MoveTool : public Tool
{
public:
    explicit MoveTool(Workspace *m_workspace,Shape *m_shape);

private:
    Shape *m_shape;

    QPoint m_start;  //鼠标移动的起始点
    QPoint m_end;    //鼠标移动的结束点

public:
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);
};

#endif // MOVETOOL_H
