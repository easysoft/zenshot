#include "textcreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

TextCreateTool::TextCreateTool(Workspace *workspace):Tool(workspace)
{

}

QString TextCreateTool::forType()
{
    return Utils::forTextKey();
}

void TextCreateTool::onMousePress(QPoint mousePoint)
{
    m_shape = new Text(m_workspace);
    m_shape->setLocation(mousePoint);

    m_workspace->addShape(m_shape);
    m_workspace->setSelected(m_shape);
    m_workspace->textAssist()->attach(m_shape);

    //执行的是新增文本编辑功能
    AddCommand *addComm = new AddCommand(m_workspace,m_shape);
    UserOper::add(addComm);
}

void TextCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{

}

void TextCreateTool::onMouseRelease(QPoint mousePoint)
{

}
