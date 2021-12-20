#include "tool.h"
#include "screen/workspace.h"

Tool::Tool(Workspace *workspace)
{
    this->m_workspace = workspace;
}

QString Tool::forType()
{
    return "base";
}

void Tool::setCursor()
{
    QPixmap pixmap(":/images/cross32.png");
    QSize pixsize(20,20);
    QPixmap scaledPixmap = pixmap.scaled(pixsize,Qt::KeepAspectRatio);
    QCursor cursor(scaledPixmap,-1,-1);

    m_workspace->widget()->setCursor(cursor);
}

