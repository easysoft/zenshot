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

#include "areacreatetool.h"
#include "screen/helper/windowgetter.h"
#include "screen/shotarea.h"
#include "screen/workspace.h"
#include "spdlogwrapper.hpp"

#include <QtCore/QtMath>

AreaCreateTool::AreaCreateTool(Workspace *wordspace):Tool(wordspace),m_isMousePress(false)
{

}

void AreaCreateTool::onMousePress(QPoint mousePoint)
{
    m_isMousePress = true;
    m_startPoint = mousePoint;
}

void AreaCreateTool::onMouseMove(QPoint mousePoint,QPoint mouseOffset)
{
    if(m_isMousePress == false)
    {
        m_workspace->autoCapture();
        m_workspace->refreshDraw();
    }
    else
    {
        //鼠标左键按下，执行手动框区域操作
        QPoint endPoint = mousePoint;

        int x = m_startPoint.x() < endPoint.x() ? m_startPoint.x() : endPoint.x();
        int y = m_startPoint.y() < endPoint.y() ? m_startPoint.y() : endPoint.y();

        int w = qAbs(m_startPoint.x() - endPoint.x());
        int h = qAbs(m_startPoint.y() - endPoint.y());

        QRect rect(x,y,w,h);
        m_workspace->setAreaBoundary(rect);
        m_workspace->refreshDraw();
    }
}

void AreaCreateTool::onMouseRelease(QPoint mousePoint)
{
    L_FUNCTION();
    m_isMousePress = false;
    //确定选择区域
    m_workspace->confirmArea();
}
