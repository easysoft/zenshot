#include "movecommand.h"
#include "screen/workspace.h"

MoveCommand::MoveCommand(Workspace *workspace,Shape *shape,QPoint offsetPoint):Command(workspace)
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
