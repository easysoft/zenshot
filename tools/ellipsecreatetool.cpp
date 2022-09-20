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

#include "ellipsecreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

EllipseCreateTool::EllipseCreateTool(Workspace *workspace):Tool(workspace)
{

}

QString EllipseCreateTool::forType()
{
    return Utils::forEllipseKey();
}

void EllipseCreateTool::onMousePress(QPoint mousePoint)
{
    m_startPoint = QPoint(mousePoint.x(),mousePoint.y());

    m_shape.reset(new Ellipse(m_workspace));
    m_shape->setBoundary(QRect(mousePoint.x(),mousePoint.y(),1,1));

    m_isInlist = false;
}

void EllipseCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_endPoint = QPoint(mousePoint.x(),mousePoint.y());

    int x = m_startPoint.x() < m_endPoint.x() ? m_startPoint.x() : m_endPoint.x();
    int y = m_startPoint.y() < m_endPoint.y() ? m_startPoint.y() : m_endPoint.y();
    int w = qAbs(m_endPoint.x() - m_startPoint.x());
    int h = qAbs(m_endPoint.y() - m_startPoint.y());

    m_shape->setBoundary(QRect(x,y,w,h));

    if(m_isInlist == false)
    {
        m_workspace->addShape(m_shape);
        m_isInlist = true;
    }

    m_workspace->refreshDraw();
}

void EllipseCreateTool::onMouseRelease(QPoint mousePoint)
{
    if(m_isInlist == false)
        return;

    m_endPoint = QPoint(mousePoint.x(),mousePoint.y());

    int x = m_startPoint.x() < m_endPoint.x() ? m_startPoint.x() : m_endPoint.x();
    int y = m_startPoint.y() < m_endPoint.y() ? m_startPoint.y() : m_endPoint.y();
    int w = qAbs(m_endPoint.x() - m_startPoint.x());
    int h = qAbs(m_endPoint.y() - m_startPoint.y());

    m_shape->setBoundary(QRect(x,y,w,h));

    if(m_shape->lineWidth() <= 4 && w < Utils::Auto_Remove_Rect && h < Utils::Auto_Remove_Rect)
    {
        m_workspace->removeShape(m_shape);
    }
    else
    {
        if(m_autoSelected == true) m_workspace->setSelected(m_shape);

        std::shared_ptr<AddCommand> addComm(new AddCommand(m_workspace,m_shape));
        UserOper::add(addComm);
    }

    m_workspace->refreshDraw();
}
