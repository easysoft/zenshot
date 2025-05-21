/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "handletool.h"

#include "spdlogwrapper.hpp"

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
    L_FUNCTION();
    m_handle->move(mousePoint);
    m_workspace->refreshDraw();
}

void HandleTool::onMouseRelease(QPoint mousePoint)
{
    QPoint  newPosition = m_handle->locator()->location();

    if(qAbs(newPosition.x()-m_pressPosition.x()) > 2 || qAbs(newPosition.y()-m_pressPosition.y()) > 2)
    {
        std::shared_ptr<LocatorCommand> locatorComm(new LocatorCommand(m_workspace,m_handle->locator(),m_pressPosition,newPosition));
        UserOper::add(locatorComm);
    }
}
