#include "rectcreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

#include <QtMath>
#include <QDebug>

RectCreateTool::RectCreateTool(Workspace *workspace):Tool(workspace)
{

}

QString RectCreateTool::forType()
{
    return Utils::forRectKey();
}

void RectCreateTool::onMousePress(QPoint mousePoint)
{
    m_startPoint = QPoint(mousePoint.x(),mousePoint.y());

    m_shape = new Rectangle(m_workspace);
    m_shape->setBoundary(QRect(mousePoint.x(),mousePoint.y(),1,1));

    m_isInlist = false;
}

void RectCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
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

void RectCreateTool::onMouseRelease(QPoint mousePoint)
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
        if(m_autoSelected == true) m_workspace->setSelected(m_shape);

        AddCommand *addComm = new AddCommand(m_workspace,m_shape);
        UserOper::add(addComm);
    }

    m_workspace->refreshDraw();
}

