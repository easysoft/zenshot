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

#include "movetool.h"
#include "spdlogwrapper.hpp"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/movecommand.h"

#include <QtMath>

MoveTool::MoveTool(Workspace *workspace, std::shared_ptr<Shape> shape):Tool(workspace)
{
    this->m_shape = shape;
}

void MoveTool::onMousePress(QPoint mousePoint)
{
    m_start = QPoint(mousePoint.x(),mousePoint.y());
    m_end = QPoint(mousePoint.x(),mousePoint.y());
}

void MoveTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    L_FUNCTION();

    m_shape->move(mouseOffset);
    m_workspace->refreshDraw();

    m_end = QPoint(mousePoint.x(),mousePoint.y());
}

void MoveTool::onMouseRelease(QPoint mousePoint)
{
    QPoint totalOffset(m_end.x()-m_start.x(), m_end.y()-m_start.y());

    if(qAbs(totalOffset.x()) > 2 || qAbs(totalOffset.y()) > 2)
    {
        MoveCommand *movComm = new MoveCommand(m_workspace,m_shape,totalOffset);
        UserOper::add(movComm);
    }
}
