/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "propscommand.h"
#include "screen/workspace.h"

PropsCommand::PropsCommand(Workspace *workspace,Shape *shape,MemoryStore oldStore,MemoryStore nowStore):Command(workspace)
{
    this->m_shape = shape;
    this->m_oldStore = oldStore;
    this->m_nowStore = nowStore;
}

void PropsCommand::undo()
{
    m_shape->loadProps(&m_oldStore);
    m_workspace->refreshDraw();
}

void PropsCommand::redo()
{
    m_shape->loadProps(&m_nowStore);
    m_workspace->refreshDraw();
}
