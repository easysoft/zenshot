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

#include "handletool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/locatorcommand.h"

#include <QtMath>

HandleTool::HandleTool(Workspace *workspace,Handle *handle):Tool(workspace)
{
    this->m_handle = handle;
}

void HandleTool::onMousePress(QPoint mousePoint)
{
    m_pressPosition = m_handle->locator()->location();
}

void HandleTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_handle->move(mousePoint);
    m_workspace->refreshDraw();
}

void HandleTool::onMouseRelease(QPoint mousePoint)
{
    QPoint  newPosition = m_handle->locator()->location();

    if(qAbs(newPosition.x()-m_pressPosition.x()) > 2 || qAbs(newPosition.y()-m_pressPosition.y()) > 2)
    {
        LocatorCommand *locatorComm = new LocatorCommand(m_workspace,m_handle->locator(),m_pressPosition,newPosition);
        UserOper::add(locatorComm);
    }
}
