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

#ifndef AREAHANDLETOOL_H
#define AREAHANDLETOOL_H

#include "core/tool.h"
#include "core/handle.h"

/**
 * @class : AreaHandleTool
 * @brief : 截图区域控制手柄操作工具类
 * @note  : 截图区域控制手柄操作工具类
 */
class AreaHandleTool : public Tool
{
public:
    explicit AreaHandleTool(Workspace *m_workspace,Handle *m_handle);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    Handle *m_handle;

};

#endif // AREAHANDLETOOL_H
