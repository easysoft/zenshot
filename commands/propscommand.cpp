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
