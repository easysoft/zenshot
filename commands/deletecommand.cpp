/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "deletecommand.h"
#include "screen/workspace.h"

DeleteCommand::DeleteCommand(Workspace *workspace, std::shared_ptr<Shape> shape):Command(workspace)
{
    this->m_shape = shape;
}

void DeleteCommand::undo()
{
    m_workspace->addShape(m_shape);
    m_workspace->refreshDraw();
}

void DeleteCommand::redo()
{
    m_workspace->removeShape(m_shape);
    m_workspace->refreshDraw();
}
