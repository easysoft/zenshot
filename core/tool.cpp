/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "tool.h"
#include "screen/workspace.h"

#include "spdlogwrapper.hpp"

Tool::Tool(Workspace *workspace)
{
    this->m_autoSelected = true;
    this->m_workspace = workspace;
}

Tool::~Tool()
{
    cleanup();
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
    //QCursor cursor(scaledPixmap,-1,-1);
    QCursor cursor(Qt::CrossCursor);

    m_workspace->widget()->setCursor(cursor);
}

void Tool::cleanup()
{
    QCursor cursor(Qt::ArrowCursor);
    m_workspace->widget()->setCursor(cursor);
}
