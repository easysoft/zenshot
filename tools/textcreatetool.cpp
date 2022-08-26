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

#include "textcreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

TextCreateTool::TextCreateTool(Workspace *workspace):Tool(workspace)
{

}

QString TextCreateTool::forType()
{
    return Utils::forTextKey();
}

void TextCreateTool::onMousePress(QPoint mousePoint)
{
    m_shape.reset(new Text(m_workspace));
    m_shape->setLocation(mousePoint);

    m_workspace->addShape(m_shape);
    m_workspace->setSelected(m_shape);
    m_workspace->textAssist()->attach(m_shape);

    //执行的是新增文本编辑功能
    AddCommand *addComm = new AddCommand(m_workspace,m_shape);
    UserOper::add(addComm);
}

void TextCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{

}

void TextCreateTool::onMouseRelease(QPoint mousePoint)
{

}
