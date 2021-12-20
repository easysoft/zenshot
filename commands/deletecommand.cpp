#include "deletecommand.h"
#include "screen/workspace.h"

DeleteCommand::DeleteCommand(Workspace *workspace,Shape *shape):Command(workspace)
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
