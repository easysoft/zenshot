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

#include "linecreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

LineCreateTool::LineCreateTool(Workspace *workspace):Tool(workspace)
{

}

QString LineCreateTool::forType()
{
    return Utils::forLineKey();
}

void LineCreateTool::onMousePress(QPoint mousePoint)
{
    m_shape.reset(new Line(m_workspace));

    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));
    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));

    m_isInlist = false;
}

void LineCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_shape->setPointAt(QPoint(mousePoint.x(),mousePoint.y()),1);

    if(m_isInlist == false)
    {
        m_workspace->addShape(m_shape);
        m_isInlist = true;
    }

    m_workspace->refreshDraw();
}

void LineCreateTool::onMouseRelease(QPoint mousePoint)
{
    if(m_isInlist == false)
        return;

    m_shape->setPointAt(QPoint(mousePoint.x(),mousePoint.y()),1);

    QPoint start = m_shape->pointAt(0);
    QPoint end = m_shape->pointAt(1);

    if(Utils::distance(start,end) < Utils::Auto_Remove_Line)
    {
        m_workspace->removeShape(m_shape);
    }
    else
    {
        if(m_autoSelected == true) m_workspace->setSelected(m_shape);

        AddCommand *addComm = new AddCommand(m_workspace,m_shape);
        UserOper::add(addComm);
    }

    m_workspace->refreshDraw();
}
