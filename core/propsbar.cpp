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

#include "propsbar.h"

#include <QFrame>
#include <QVariant>

#include "screen/workspace.h"

PropsBar::PropsBar(Workspace *workspace):QWidget(workspace->widget())
{
    setAttribute(Qt::WA_StyledBackground);

    this->m_store = new LocalStore();
    this->m_workspace = workspace;
    this->setProperty("class","bar");
    this->setCursor(Qt::ArrowCursor);

    m_layout = new QHBoxLayout(this);
    this->setLayout(m_layout);

    m_layout->setContentsMargins(ts(3),ts(2),ts(3),ts(2));

}

void PropsBar::addSeperator()
{
    //分割线组件构造添加
    QFrame *splite = new QFrame();
    splite->setObjectName("vSplit2");
    splite->setFrameShape(QFrame::VLine);
    m_layout->addWidget(splite);
}

void PropsBar::propsChanged()
{
    saveProps();
    m_workspace->refreshProps();
}
