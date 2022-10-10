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

#ifndef HITTOOL_H
#define HITTOOL_H

#include "core/tool.h"
#include "core/handle.h"
#include "core/shape.h"

/**
 * @class : HoverTool
 * @brief : 悬停工具类定义
 * @note  : 鼠标悬停辅助工具类定义
 */
class HoverTool : public Tool
{
public:
    explicit HoverTool(Workspace *m_workspace);

public:

    /**
     * @brief 获取可被命中图形上的控制手柄
     * @return
     */
    Handle *shapeHandle() const;

    /**
     * @brief 获取可被命中截图区域上的控制手柄
     * @return
     */
    Handle *shotAeaHandle() const;

    /**
     * @brief 获取可被命中的图形
     * @return
     */
    std::shared_ptr<Shape> shape() const;

    /**
     * @brief 获取截图区域本身是否可被命中
     * @return
     */
    bool shotAreaSelf() const;

    /**
     * @brief 根据给定坐标重新判断可被命中的元素
     * @param mousePoint
     */
    void refresh(QPoint mousePoint);

    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    bool m_shotAreaSelf;
    std::shared_ptr<Shape> m_shape;
    Handle *m_shapeHandle;
    Handle *m_shotAreaHandle;

    void setCursor(QPoint mousePoint);
};

#endif // HITTOOL_H
