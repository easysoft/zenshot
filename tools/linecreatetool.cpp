#include "linecreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

LineCreateTool::LineCreateTool(Workspace *workspace):Tool(workspace)
{

}

QString LineCreateTool::forType()
{
    return Utils::forLineKey();
}

void LineCreateTool::onMousePress(QPoint mousePoint)
{
    m_shape = new Line(m_workspace);

    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));
    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));

    m_isInlist = false;
}

void LineCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_shape->setPointAt(QPoint(mousePoint.x(),mousePoint.y()),1);

    if(m_isInlist == false)
    {
        m_workspace->addShape(m_shape);
        m_isInlist = true;
    }

    m_workspace->refreshDraw();
}

void LineCreateTool::onMouseRelease(QPoint mousePoint)
{
    if(m_isInlist == false)
        return;

    m_shape->setPointAt(QPoint(mousePoint.x(),mousePoint.y()),1);

    QPoint start = m_shape->pointAt(0);
    QPoint end = m_shape->pointAt(1);

    if(Utils::distance(start,end) < Utils::Auto_Remove_Line)
    {
        m_workspace->removeShape(m_shape);
    }
    else
    {
        if(m_autoSelected == true) m_workspace->setSelected(m_shape);

        AddCommand *addComm = new AddCommand(m_workspace,m_shape);
        UserOper::add(addComm);
    }

    m_workspace->refreshDraw();
}
