/* Copyright (C) 2021 Nature Easy Soft Network Technology Co., LTD
 *
 * This file is part of Zenshot (https://github.com/easysoft/zenshot/).
 *
 * Zenshot is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zenshot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zenshot. If not, see <https://www.gnu.org/licenses/>.
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

    L_DEBUG("Set Mosaic Cursor");
}

void MosaicCreateTool::onMousePress(QPoint mousePoint)
{
    m_shape = new Mosaic(m_workspace);

    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));

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

    AddCommand *addComm = new AddCommand(m_workspace,m_shape);
    UserOper::add(addComm);

    L_DEBUG("Clear Mosaic Cursor");
}

