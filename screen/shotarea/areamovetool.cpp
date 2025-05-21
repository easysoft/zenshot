/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "areamovetool.h"
#include "screen/workspace.h"

#include "spdlogwrapper.hpp"


AreaMoveTool::AreaMoveTool(Workspace *workspace):Tool(workspace)
{

}

void AreaMoveTool::onMousePress(QPoint mousePoint)
{

}

void AreaMoveTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    L_FUNCTION();
    m_workspace->moveArea(mouseOffset);

    QRectF areaRect = m_workspace->areaBoundary();
    QRectF screenRect = m_workspace->limitBoundary();

    QPoint locPoint(areaRect.x(),areaRect.y());

    if(areaRect.x() < screenRect.x())
        locPoint.setX(screenRect.x());
    else if(areaRect.x() + areaRect.width() > screenRect.x() + screenRect.width())
        locPoint.setX(screenRect.x() + screenRect.width() - areaRect.width());

    if(areaRect.y() < screenRect.y())
        locPoint.setY(screenRect.y());
    else if(areaRect.y()+areaRect.height() > screenRect.y()+screenRect.height())
        locPoint.setY(screenRect.y() + screenRect.height() - areaRect.height());

    QRect trimedRect(locPoint.x(),locPoint.y(),areaRect.width(),areaRect.height());

    m_workspace->setAreaBoundary(trimedRect);
    m_workspace->refreshDraw();
    m_workspace->rePositionBar();
}

void AreaMoveTool::onMouseRelease(QPoint mousePoint)
{

}
