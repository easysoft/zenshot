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

#include "movecommand.h"
#include "screen/workspace.h"

MoveCommand::MoveCommand(Workspace *workspace, std::shared_ptr<Shape> shape,QPoint offsetPoint):Command(workspace)
{
    this->m_shape = shape;
    this->m_offsetPoint = QPoint(offsetPoint.x(),offsetPoint.y());
}

void MoveCommand::undo()
{
    m_shape->move(QPoint(-m_offsetPoint.x(),-m_offsetPoint.y()));
    m_workspace->refreshDraw();
}

void MoveCommand::redo()
{
    m_shape->move(QPoint(m_offsetPoint.x(),m_offsetPoint.y()));
    m_workspace->refreshDraw();
}
