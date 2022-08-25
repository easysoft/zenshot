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

#ifndef TOOL_H
#define TOOL_H

#include <QMouseEvent>
#include <QPoint>

#include "core/utils.h"

#include <memory>

class Workspace;

/**
 * @class : Tool
 * @brief : 鼠标功能基类定义
 * @note  : 涉及到鼠标互操作相关功能定义
 */
class Tool
{
public:
    /**
     * @brief Tool
     * @param workspace 工作空间
     */
    explicit Tool(Workspace *m_workspace);

    /**
     * @brief 获取对应的图形类型(针对 create 类的 tool)
     * @return
     */
    virtual QString forType();

    /**
     * @brief 鼠标按下事件回调处理
     * @param mousePoint 鼠标当前位置
     */
    virtual void onMousePress(QPoint mousePoint)=0;

    /**
     * @brief 鼠标移动事件回调处理
     * @param mousePoint 鼠标当前位置
     * @param mouseOffset 鼠标移动偏移量
     */
    virtual void onMouseMove(QPoint mousePoint,QPoint mouseOffset)=0;

    /**
     * @brief 鼠标弹起事件回调处理
     * @param mousePoint 鼠标当前位置
     */
    virtual void onMouseRelease(QPoint mousePoint)=0;

    /**
     * @brief 设置鼠标形状
     */
    virtual void setCursor();

    virtual void cleanup();
protected:
    bool m_autoSelected;
    Workspace *m_workspace;
};

#endif // TOOL_H
