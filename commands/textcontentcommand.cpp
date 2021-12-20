#include "textcontentcommand.h"
#include "screen/workspace.h"

TextContentCommand::TextContentCommand(Workspace *workspace,Text *shape,QString preContent):Command(workspace)
{
    this->m_shape = shape;
    m_oldContent = preContent;
    m_nowContent = m_shape->content();
}

void TextContentCommand::undo()
{
    m_shape->setContent(m_oldContent);
    m_workspace->refreshDraw();
}

void TextContentCommand::redo()
{
    m_shape->setContent(m_nowContent);
    m_workspace->refreshDraw();
}
