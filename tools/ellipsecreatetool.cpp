#include "ellipsecreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

EllipseCreateTool::EllipseCreateTool(Workspace *workspace):Tool(workspace)
{

}

QString EllipseCreateTool::forType()
{
    return Utils::forEllipseKey();
}

void EllipseCreateTool::onMousePress(QPoint mousePoint)
{
    m_startPoint = QPoint(mousePoint.x(),mousePoint.y());

    m_shape = new Ellipse(m_workspace);
    m_shape->setBoundary(QRect(mousePoint.x(),mousePoint.y(),1,1));

    m_isInlist = false;
}

void EllipseCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_endPoint = QPoint(mousePoint.x(),mousePoint.y());

    int x = m_startPoint.x() < m_endPoint.x() ? m_startPoint.x() : m_endPoint.x();
    int y = m_startPoint.y() < m_endPoint.y() ? m_startPoint.y() : m_endPoint.y();
    int w = qAbs(m_endPoint.x() - m_startPoint.x());
    int h = qAbs(m_endPoint.y() - m_startPoint.y());

    m_shape->setBoundary(QRect(x,y,w,h));

    if(m_isInlist == false)
    {
        m_workspace->addShape(m_shape);
        m_isInlist = true;
    }

    m_workspace->refreshDraw();
}

void EllipseCreateTool::onMouseRelease(QPoint mousePoint)
{
    if(m_isInlist == false)
        return;

    m_endPoint = QPoint(mousePoint.x(),mousePoint.y());

    int x = m_startPoint.x() < m_endPoint.x() ? m_startPoint.x() : m_endPoint.x();
    int y = m_startPoint.y() < m_endPoint.y() ? m_startPoint.y() : m_endPoint.y();
    int w = qAbs(m_endPoint.x() - m_startPoint.x());
    int h = qAbs(m_endPoint.y() - m_startPoint.y());

    m_shape->setBoundary(QRect(x,y,w,h));

    if(m_shape->lineWidth() <= 4 && w < Utils::Auto_Remove_Rect && h < Utils::Auto_Remove_Rect)
    {
        m_workspace->removeShape(m_shape);
    }
    else
    {
        AddCommand *addComm = new AddCommand(m_workspace,m_shape);
        UserOper::add(addComm);
    }

    m_workspace->refreshDraw();
}
