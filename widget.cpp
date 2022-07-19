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
    , m_status("unknown")
{
    setWindowFlag(Qt::FramelessWindowHint);
#ifndef USE_SPDLOG_
    setAttribute(Qt::WA_TranslucentBackground);
#endif // USE_SPDLOG_

    setWindowFlags(windowFlags()
#ifndef USE_SPDLOG_
        | Qt::Tool
#endif // USE_SPDLOG_
    );

    //测试的时候去掉置顶，否则一些导致调试器奔溃的Bug会让机器直接没招
#ifdef Q_OS_WIN32
#ifndef USE_SPDLOG_
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
#endif // USE_SPDLOG_
#endif

    setMouseTracking(true);
}

Widget::~Widget()
{
    L_ERROR("{0}", __FUNCTION__);

    delete m_workspace;
    m_workspace = nullptr;
}

void Widget::start(std::shared_ptr<ScreenList> list)
{
    L_FUNCTION();

    m_screenlist = list;
    m_workspace->start(m_screenlist);

    QRect geometry = list->allBoundary(true);
    setGeometry(geometry);

    setEnabled(true);

    showFullScreen();
    
    L_TRACE("is visable = {0} && x: {1}, y: {2}, w: {3}, h: {4} & geometry[{5}, {6}, {7}, {8}]$$$m_status ={9}", this->isVisible(), pos().x(), pos().y(), size().width(), size().height(), geometry.left(), geometry.top(), geometry.right(), geometry.bottom(), m_status.toStdString().c_str());
}

void Widget::cleanup()
{
    L_FUNCTION();
    hide();

    L_TRACE("is visable = {0} && w: {1}, h: {2}", this->isVisible(), size().width(), size().height());

    m_status = "unknown";
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

void Widget::showEvent(QShowEvent* event)
{
    L_FUNCTION();
	raise();
	activateWindow();

    L_WARN("is visable = {0} && x: {1}, y: {2}, w: {3}, h: {4}", this->isVisible(), pos().x(), pos().y(), size().width(), size().height(), m_status.toStdString().c_str());
}

void Widget::closeEvent(QCloseEvent* event)
{
    hide();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(m_status != "giveup")
        m_workspace->onMousePress(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    L_TRACE("{0} stat = {1}", __FUNCTION__, m_status.toStdString().c_str());
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
    L_FUNCTION();
    QPainter painter(this);

    m_workspace->draw(painter);
}

void Widget::enterEvent(QEvent* event)
{
    L_FUNCTION();
    L_DEBUG("*************************************************");
}

void Widget::leaveEvent(QEvent *event)
{
    L_FUNCTION();
    if(m_workspace->areaConfirmed() == false)
    {
        L_DEBUG("..............................................");
        setEnabled(false);
//         m_workspace->setAreaBoundary(QRect(0,0,0,0));
//         update();
    }
}



