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

    m_layout->setContentsMargins(5,3,5,3);

}

void PropsBar::addSeperator()
{
    //分割线组件构造添加
    QFrame *splite = new QFrame();
    splite->setObjectName("vLSplit");
    splite->setFrameShape(QFrame::VLine);
    m_layout->addWidget(splite);
}

void PropsBar::propsChanged()
{
    saveProps();
    m_workspace->refreshProps();
}
