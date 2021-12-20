#include "movetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/movecommand.h"

#include <QtMath>

MoveTool::MoveTool(Workspace *workspace,Shape *shape):Tool(workspace)
{
    this->m_shape = shape;
}

void MoveTool::onMousePress(QPoint mousePoint)
{
    m_start = QPoint(mousePoint.x(),mousePoint.y());
    m_end = QPoint(mousePoint.x(),mousePoint.y());
}

void MoveTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_shape->move(mouseOffset);
    m_workspace->refreshDraw();

    m_end = QPoint(mousePoint.x(),mousePoint.y());
}

void MoveTool::onMouseRelease(QPoint mousePoint)
{
    QPoint totalOffset(m_end.x()-m_start.x(), m_end.y()-m_start.y());

    if(qAbs(totalOffset.x()) > 2 || qAbs(totalOffset.y()) > 2)
    {
        MoveCommand *movComm = new MoveCommand(m_workspace,m_shape,totalOffset);
        UserOper::add(movComm);
    }
}
