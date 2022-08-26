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

#include "curvecreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

CurveCreateTool::CurveCreateTool(Workspace *workspace):Tool(workspace)
{

}

QString CurveCreateTool::forType()
{
    return Utils::forCurveKey();
}

void CurveCreateTool::onMousePress(QPoint mousePoint)
{
    m_shape.reset(new Curve(m_workspace));

    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));

    m_workspace->addShape(m_shape);
}

void CurveCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));
    m_workspace->refreshDraw();
}

void CurveCreateTool::onMouseRelease(QPoint mousePoint)
{
    m_shape->setPointAt(QPoint(mousePoint.x(),mousePoint.y()),m_shape->count()-1);


    if(m_shape->count() < 2)
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

