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

    L_DEBUG("$$$$$$$$$$ 0x{0:x} set cross32", (uint64_t)this);
}

void Tool::cleanup()
{
    QCursor cursor(Qt::ArrowCursor);
    m_workspace->widget()->setCursor(cursor);

    L_INFO("********* 0x{0:x} set ArrowCursor", (uint64_t)this);
}
