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

#include "areamovetool.h"
#include "screen/workspace.h"

#include "../spdlogwrapper.hpp"


AreaMoveTool::AreaMoveTool(Workspace *workspace):Tool(workspace)
{

}

void AreaMoveTool::onMousePress(QPoint mousePoint)
{

}

void AreaMoveTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    L_FUNCTION();
    m_workspace->moveArea(mouseOffset);

    QRectF areaRect = m_workspace->areaBoundary();
    QRectF screenRect = m_workspace->limitBoundary();

    QPoint locPoint(areaRect.x(),areaRect.y());

    if(areaRect.x() < screenRect.x())
        locPoint.setX(screenRect.x());
    else if(areaRect.x() + areaRect.width() > screenRect.x() + screenRect.width())
        locPoint.setX(screenRect.x() + screenRect.width() - areaRect.width());

    if(areaRect.y() < screenRect.y())
        locPoint.setY(screenRect.y());
    else if(areaRect.y()+areaRect.height() > screenRect.y()+screenRect.height())
        locPoint.setY(screenRect.y() + screenRect.height() - areaRect.height());

    QRect trimedRect(locPoint.x(),locPoint.y(),areaRect.width(),areaRect.height());

    m_workspace->setAreaBoundary(trimedRect);
    m_workspace->refreshDraw();
    m_workspace->rePositionBar();
}

void AreaMoveTool::onMouseRelease(QPoint mousePoint)
{

}
