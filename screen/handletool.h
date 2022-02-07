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

#ifndef HANDLETOOL_H
#define HANDLETOOL_H

#include "core/tool.h"
#include "core/handle.h"

/**
 * @class : HandleTool
 * @brief : 控制手柄操作工具类定义
 * @note  : 提供控制手柄的移动功能
 */
class HandleTool : public Tool
{
public:
    /**
     * @brief HandleTool
     * @param m_workspace 工作空间
     * @param m_handle 目标控制手柄
     */
    explicit HandleTool(Workspace *m_workspace,Handle *m_handle);

private:
    QPoint m_pressPosition;  //鼠标按下时的坐标
    Handle *m_handle;        //要操作的控制手柄

public:
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);
};

#endif // HANDLETOOL_H
