#include "areahandletool.h"
#include "screen/workspace.h"

AreaHandleTool::AreaHandleTool(Workspace *workspace,Handle *handle):Tool(workspace)
{
    this->m_handle = handle;
}

QString AreaHandleTool::forType()
{
    return "ShotAreaHandle";
}

void AreaHandleTool::onMousePress(QPoint mousePoint)
{

}

void AreaHandleTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    QRect rect = m_workspace->limitBoundary();

    int x = mousePoint.x();
    int y = mousePoint.y();

    if(x < rect.x())
        x = rect.x();
    else if(x > rect.x() + rect.width())
        x = rect.x() + rect.width();

    if(y < rect.y())
        y = rect.y();
    else if(y > rect.y() + rect.height())
        y = rect.y() + rect.height();

    QPoint trimedPoint(x,y);


    m_handle->move(trimedPoint);
    m_workspace->refreshDraw();
    m_workspace->rePositionBar();
}

void AreaHandleTool::onMouseRelease(QPoint mousePoint)
{

}
