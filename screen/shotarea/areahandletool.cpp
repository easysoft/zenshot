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

#include "areahandletool.h"
#include "screen/workspace.h"

AreaHandleTool::AreaHandleTool(Workspace *workspace,Handle *handle):Tool(workspace)
{
    this->m_handle = handle;
}

QString AreaHandleTool::forType()
{
    return "ShotAreaHandle";
}

void AreaHandleTool::onMousePress(QPoint mousePoint)
{

}

void AreaHandleTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    QRect rect = m_workspace->limitBoundary();

    int x = mousePoint.x();
    int y = mousePoint.y();

    if(x < rect.x())
        x = rect.x();
    else if(x > rect.x() + rect.width())
        x = rect.x() + rect.width();

    if(y < rect.y())
        y = rect.y();
    else if(y > rect.y() + rect.height())
        y = rect.y() + rect.height();

    QPoint trimedPoint(x,y);


    m_handle->move(trimedPoint);
    m_workspace->refreshDraw();
    m_workspace->rePositionBar();
}

void AreaHandleTool::onMouseRelease(QPoint mousePoint)
{

}
