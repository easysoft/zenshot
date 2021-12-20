#include "areamovetool.h"
#include "screen/workspace.h"


AreaMoveTool::AreaMoveTool(Workspace *workspace):Tool(workspace)
{

}

void AreaMoveTool::onMousePress(QPoint mousePoint)
{

}

void AreaMoveTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
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
