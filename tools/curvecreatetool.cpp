#include "curvecreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

CurveCreateTool::CurveCreateTool(Workspace *workspace):Tool(workspace)
{

}

QString CurveCreateTool::forType()
{
    return Utils::forCurveKey();
}

void CurveCreateTool::onMousePress(QPoint mousePoint)
{
    m_shape = new Curve(m_workspace);

    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));

    m_workspace->addShape(m_shape);
}

void CurveCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));
    m_workspace->refreshDraw();
}

void CurveCreateTool::onMouseRelease(QPoint mousePoint)
{
    m_shape->setPointAt(QPoint(mousePoint.x(),mousePoint.y()),m_shape->count()-1);


    if(m_shape->count() < 2)
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

