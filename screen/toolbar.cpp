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

#include "toolbar.h"

#include "spdlogwrapper.hpp"

#include <QVariant>
#include <QApplication>

#include "screen/workspace.h"
#include "core/utils.h"
#include "core/useroper.h"
#include "starterui.h"

extern StarterUI* g_start_ui_;

ToolBar::ToolBar(Workspace *workspace)
    : QWidget(workspace->widget())
    , m_layout()
    , btnGroup(this)
    , m_undoBtn(nullptr)
    , m_redoBtn(nullptr)
{
    setAttribute(Qt::WA_StyledBackground);

    this->m_workspace = workspace;

    this->setProperty("class","bar");
    this->setCursor(Qt::ArrowCursor);

    createChild();

    L_WARN("{0}, {1}", __FUNCTION__, __LINE__);
}

ToolBar::~ToolBar()
{
    L_WARN("{0}, {1}", __FUNCTION__, __LINE__);
}

void ToolBar::createChild()
{
    m_layout.setContentsMargins(ts(4),ts(2),ts(4),ts(2));
    m_layout.setSpacing(ts(0));

    this->setLayout(&m_layout);

    createCreateButtons();
    createFunctionButons();

    connect(UserOper::instance(),SIGNAL(changed()),this,SLOT(operChanged()));
}

void ToolBar::addSeperator()
{
    m_layout.addSpacing(ts(3));

    QFrame *splite = new QFrame();
    splite->setObjectName("vSplit");
    splite->setFrameShape(QFrame::VLine);
    splite->setLineWidth(ts(1));
    m_layout.addWidget(splite);

    m_layout.addSpacing(ts(2));
}

void ToolBar::highlightCreateBtn(QString shapeType)
{
    int index = m_createBtnKeyList.indexOf(shapeType);
    QAbstractButton *btn = btnGroup.button(index);

    btn->setChecked(true);
}

void ToolBar::cleanup()
{
    btnGroup.setExclusive(false);
    for (auto btn : btnGroup.buttons())
    {
        btn->setChecked(false);
    }
    btnGroup.setExclusive(true);

    operChanged();
}

void ToolBar::createCreateButtons()
{
    createSingleCreateButton(&btnGroup,Utils::forRectKey(),QChar(0xe906),tr("rectangle"));
    createSingleCreateButton(&btnGroup,Utils::forEllipseKey(),QChar(0xe903),tr("ellipse"));
    createSingleCreateButton(&btnGroup,Utils::forLineKey(),QChar(0xe905),tr("line"));
    createSingleCreateButton(&btnGroup,Utils::forArrowKey(),QChar(0xe900),tr("arrow"));
    createSingleCreateButton(&btnGroup,Utils::forCurveKey(),QChar(0xe90a),tr("pie"));
    createSingleCreateButton(&btnGroup,Utils::forTextKey(),QChar(0xe90b),tr("text"));
    createSingleCreateButton(&btnGroup,Utils::forMosaicKey(),QChar(0xe909),tr("mosaic"));

    btnGroup.setExclusive(true);

    connect(&btnGroup,SIGNAL(buttonClicked(int)),this,SLOT(createBtnClicked(int)));
}

void ToolBar::createFunctionButons()
{
    addSeperator();

    m_undoBtn = createSingleFunctionButton(QChar(0xe908),tr("undo"));
    m_redoBtn = createSingleFunctionButton(QChar(0xe90c),tr("redo"));

    m_undoBtn->setEnabled(false);
    m_redoBtn->setEnabled(false);

    addSeperator();

    QPushButton *downloadBtn = createSingleFunctionButton(QChar(0xe907),tr("download"));
    QPushButton *closeBtn = createSingleFunctionButton(QChar(0xe904),tr("exit"),"cancelBtn");
    QPushButton *clipboardBtn = createSingleFunctionButton(QChar(0xe902),tr("finish"),"saveBtn");
#if !NZENTAO_VER_
    QPushButton *send2ZenTaoBtn = createSingleFunctionButton(QChar(0xe90e), tr("send2zentao"), "sendBtn");

    send2ZenTaoBtn->setProperty("forTip", "mainBtnLight");
#endif // NZENTAO_VER_

    connect(m_undoBtn,SIGNAL(clicked()),this,SLOT(undo()));
    connect(m_redoBtn,SIGNAL(clicked()),this,SLOT(redo()));

    connect(downloadBtn,SIGNAL(clicked()),this,SLOT(downloadBtnClicked()));
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(closeProgramBtnClicked()));
    connect(clipboardBtn,SIGNAL(clicked()),this,SLOT(saveBtnClicked()));
#if !NZENTAO_VER_
    connect(send2ZenTaoBtn, SIGNAL(clicked()), this, SLOT(OnShowPreviewClicked()));
    connect(this, SIGNAL(ShowPreview(Workspace*)), g_start_ui_, SLOT(OnShowPreview(Workspace*)));
#endif // NZENTAO_VER_
}

void ToolBar::createSingleCreateButton(QButtonGroup *group, QString shapeType, QString iconStr,QString tipStr)
{
    QPushButton *btn = new QPushButton();

    btn->setObjectName(shapeType);
    btn->setCheckable(true);
    btn->setProperty("forTip","mainBtn");
    btn->setText(iconStr);
    btn->setToolTip(tipStr);

    group->addButton(btn,m_createBtnKeyList.count());
    m_layout.addWidget(btn);

    m_createBtnKeyList.append(shapeType);
}

QPushButton *ToolBar::createSingleFunctionButton(QString iconStr,QString tipStr,QString objectName)
{
    QPushButton *btn = new QPushButton();

    if(objectName.isEmpty() == false)
    {
        btn->setObjectName(objectName);
    }

    btn->setProperty("forTip","mainBtn");
    //btn->setFont(m_workspace->iconfont());
    btn->setText(iconStr);

    btn->setToolTip(tipStr);

    m_layout.addWidget(btn);

    return btn;
}

void ToolBar::undo()
{
    m_workspace->normalbeforeUndo();
    UserOper::undo();
}

void ToolBar::redo()
{
    UserOper::redo();
}

void ToolBar::operChanged()
{
    m_undoBtn->setEnabled(UserOper::undoNum()>0);
    m_redoBtn->setEnabled(UserOper::redoNum()>0);
}

void ToolBar::createBtnClicked(int index)
{
    QString shapeType = m_createBtnKeyList[index];

    emit createChanged(shapeType);
}

void ToolBar::downloadBtnClicked()
{
    L_INFO("downloadBtnClicked");
    emit download();
}

void ToolBar::closeProgramBtnClicked()
{
    emit closeProgram();
}

void ToolBar::saveBtnClicked()
{
    emit save();
}

#if !NZENTAO_VER_
void ToolBar::OnShowPreviewClicked()
{
    emit ShowPreview(m_workspace);
}
#endif // NZENTAO_VER_
