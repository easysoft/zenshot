/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "mosaiccreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

#include "spdlogwrapper.hpp"

MosaicCreateTool::MosaicCreateTool(Workspace *workspace) : Tool(workspace)
{

}

QString MosaicCreateTool::forType()
{
    return Utils::forMosaicKey();
}

void MosaicCreateTool::setCursor()
{
    QPixmap pixmap(":/images/mosaic.png");
    QSize pixsize(18,18);
    QPixmap scaledPixmap = pixmap.scaled(pixsize,Qt::KeepAspectRatio);
    QCursor cursor(scaledPixmap,-1,-1);

    m_workspace->widget()->setCursor(cursor);

    L_DEBUG("@@@@@@@@@@ 0x{0:x} Set Mosaic Cursor", (uint64_t)this);
}

void MosaicCreateTool::onMousePress(QPoint mousePoint)
{
    m_shape.reset(new Mosaic(m_workspace));

    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));

    L_WARN("add moscaic +++++++++++");
    m_workspace->addMosaic(m_shape);
}

void MosaicCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));
    m_workspace->refreshDraw();
}

void MosaicCreateTool::onMouseRelease(QPoint mousePoint)
{
    m_workspace->refreshDraw();

    std::shared_ptr<AddCommand> addComm(new AddCommand(m_workspace,m_shape));
    UserOper::add(addComm);
}
