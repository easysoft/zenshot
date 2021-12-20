#include "handletool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/locatorcommand.h"

#include <QtMath>

HandleTool::HandleTool(Workspace *workspace,Handle *handle):Tool(workspace)
{
    this->m_handle = handle;
}

void HandleTool::onMousePress(QPoint mousePoint)
{
    m_pressPosition = m_handle->locator()->location();
}

void HandleTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_handle->move(mousePoint);
    m_workspace->refreshDraw();
}

void HandleTool::onMouseRelease(QPoint mousePoint)
{
    QPoint  newPosition = m_handle->locator()->location();

    if(qAbs(newPosition.x()-m_pressPosition.x()) > 2 || qAbs(newPosition.y()-m_pressPosition.y()) > 2)
    {
        LocatorCommand *locatorComm = new LocatorCommand(m_workspace,m_handle->locator(),m_pressPosition,newPosition);
        UserOper::add(locatorComm);
    }
}
