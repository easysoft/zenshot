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
