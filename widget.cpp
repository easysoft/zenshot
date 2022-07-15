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

#include "widget.h"

#include "spdlogwrapper.hpp"
#include <QPainter>

#include <QBitmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_workspace(new Workspace(this))
    , m_screenlist(nullptr)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    setWindowFlags(windowFlags() | Qt::Tool);

    //测试的时候去掉置顶，否则一些导致调试器奔溃的Bug会让机器直接没招
#ifdef Q_OS_WIN32
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
#endif

    setMouseTracking(true);
}

Widget::~Widget()
{
    L_TRACE("{0} @ {1}", __FUNCTION__, __LINE__);

    delete m_workspace;
    m_workspace = nullptr;
}

void Widget::start(std::shared_ptr<ScreenList> list)
{
    L_TRACE("{0} @ {1}", __FUNCTION__, __LINE__);

    m_screenlist = list;
    m_status = "unknown";
    m_workspace->start(m_screenlist);

    QRect geometry = list->allBoundary(true);
    setGeometry(geometry);

    showFullScreen();
}

void Widget::cleanup()
{
    L_TRACE("{0} @ {1}", __FUNCTION__, __LINE__);
    m_status = "unknown";
    hide();
    m_workspace->cleanup();
}

Workspace* Widget::workspace() const
{
    return m_workspace;
}

void Widget::finishConfirmArea()
{
    if(m_workspace->areaConfirmed() == true)
        m_status = "active";
    else
        m_status = "giveup";
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(m_status != "giveup")
        m_workspace->onMousePress(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_status != "giveup")
        m_workspace->onMouseMove(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_status != "giveup")
        m_workspace->onMouseRelease(event);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
   m_workspace->onKeyPress(event);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    m_workspace->draw(painter);
}

void Widget::leaveEvent(QEvent *event)
{
    if(m_workspace->areaConfirmed() == false)
    {
        m_workspace->setAreaBoundary(QRect(0,0,0,0));
        update();
    }
}



