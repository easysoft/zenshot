/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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
    m_shape.reset(new Curve(m_workspace));

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

        std::shared_ptr<AddCommand> addComm(new AddCommand(m_workspace,m_shape));
        UserOper::add(addComm);
    }

    m_workspace->refreshDraw();
}

