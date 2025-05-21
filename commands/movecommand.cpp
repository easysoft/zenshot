/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "movecommand.h"
#include "screen/workspace.h"

MoveCommand::MoveCommand(Workspace *workspace, std::shared_ptr<Shape> shape,QPoint offsetPoint):Command(workspace)
{
    this->m_shape = shape;
    this->m_offsetPoint = QPoint(offsetPoint.x(),offsetPoint.y());
}

void MoveCommand::undo()
{
    m_shape->move(QPoint(-m_offsetPoint.x(),-m_offsetPoint.y()));
    m_workspace->refreshDraw();
}

void MoveCommand::redo()
{
    m_shape->move(QPoint(m_offsetPoint.x(),m_offsetPoint.y()));
    m_workspace->refreshDraw();
}
