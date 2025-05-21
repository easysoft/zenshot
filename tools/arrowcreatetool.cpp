/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "arrowcreatetool.h"
#include "screen/workspace.h"
#include "core/utils.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

ArrowCreateTool::ArrowCreateTool(Workspace *workspace):Tool(workspace)
{

}

QString ArrowCreateTool::forType()
{
    return Utils::forArrowKey();
}

void ArrowCreateTool::onMousePress(QPoint mousePoint)
{
    m_shape.reset(new Arrow(m_workspace));

    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));
    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));

    m_isInlist = false;
}

void ArrowCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_shape->setPointAt(QPoint(mousePoint.x(),mousePoint.y()),1);

    if(m_isInlist == false)
    {
        m_workspace->addShape(m_shape);
        m_isInlist = true;
    }

    m_workspace->refreshDraw();
}

void ArrowCreateTool::onMouseRelease(QPoint mousePoint)
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

        std::shared_ptr<AddCommand> addComm(new AddCommand(m_workspace,m_shape));
        UserOper::add(addComm);
    }

    m_workspace->refreshDraw();
}


