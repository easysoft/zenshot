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

#include "addcommand.h"
#include "screen/workspace.h"

AddCommand::AddCommand(Workspace *workspace,Shape *shape):Command(workspace)
{
    this->m_shape = shape;
}

void AddCommand::undo()
{
    m_workspace->removeShape(m_shape);
    m_workspace->refreshDraw();
}

void AddCommand::redo()
{
    m_workspace->addShape(m_shape);
    m_workspace->refreshDraw();
}
