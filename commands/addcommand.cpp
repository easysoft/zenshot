#include "addcommand.h"
#include "screen/workspace.h"

AddCommand::AddCommand(Workspace *workspace,Shape *shape):Command(workspace)
{
    this->m_shape = shape;
}

void AddCommand::undo()
{
    m_workspace->removeShape(m_shape);
    m_workspace->refreshDraw();
}

void AddCommand::redo()
{
    m_workspace->addShape(m_shape);
    m_workspace->refreshDraw();
}
