/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "movetool.h"
#include "spdlogwrapper.hpp"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/movecommand.h"

#include <QtMath>

MoveTool::MoveTool(Workspace *workspace, std::shared_ptr<Shape> shape):Tool(workspace)
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
    L_FUNCTION();

    m_shape->move(mouseOffset);
    m_workspace->refreshDraw();

    m_end = QPoint(mousePoint.x(),mousePoint.y());
}

void MoveTool::onMouseRelease(QPoint mousePoint)
{
    QPoint totalOffset(m_end.x()-m_start.x(), m_end.y()-m_start.y());

    if(qAbs(totalOffset.x()) > 2 || qAbs(totalOffset.y()) > 2)
    {
        std::shared_ptr<MoveCommand> movComm(new MoveCommand(m_workspace,m_shape,totalOffset));
        UserOper::add(movComm);
    }
}
