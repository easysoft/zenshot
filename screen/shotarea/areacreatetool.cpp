/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
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
    L_FUNCTION();
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
