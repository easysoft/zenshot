/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
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

    m_layout->setContentsMargins(ts(3),ts(3),ts(3),ts(3));  //ts(3),ts(2),ts(3),ts(2)

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
