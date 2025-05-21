/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "locatorcommand.h"
#include "screen/workspace.h"

LocatorCommand::LocatorCommand(Workspace *workspace,Locator *locator,QPoint oldPosition, QPoint newPosition):Command(workspace)
{
    this->m_locator = locator;
    this->m_newPosition = newPosition;
    this->m_oldPosition = oldPosition;
}

void LocatorCommand::undo()
{
    m_locator->setLocation(m_oldPosition);
    m_workspace->refreshDraw();
}

void LocatorCommand::redo()
{
    m_locator->setLocation(m_newPosition);
    m_workspace->refreshDraw();
}
