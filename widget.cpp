/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "widget.h"

#include "spdlogwrapper.hpp"
#include <QPainter>

#include <QBitmap>

#define UNVISIABLE_X -819200
#define UNVISIABLE_Y -819200

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , m_workspace(new Workspace(this))
    , m_screenlist(nullptr)
    , m_status("unknown")
{
#ifndef USE_SPDLOG_
    setWindowFlags(Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
#endif // USE_SPDLOG_
}

Widget::~Widget()
{
    L_ERROR("{0}", __FUNCTION__);
}

void Widget::start(std::shared_ptr<ScreenList> list, int index)
{
    L_FUNCTION();

	QRect geometry = list->allBoundary(true);
	setGeometry(geometry);

    showFullScreen();

    raise();
    activateWindow();

    setCursor(Qt::ArrowCursor);

	m_screenlist = list;
	m_workspace->start(m_screenlist, index);
}

void Widget::cleanup()
{
    L_FUNCTION();
    hide();

    L_TRACE("is visable = {0} && w: {1}, h: {2} @ {3}", this->isVisible(), size().width(), size().height(), __FUNCTION__);

    m_status = "unknown";
    m_workspace->cleanup();

    update();
}

Workspace* Widget::workspace() const
{
    return m_workspace;
}

void Widget::finishConfirmArea()
{
    if (m_workspace->areaConfirmed() == true)
        m_status = "active";
    else
        m_status = "giveup";
}

void Widget::showEvent(QShowEvent* event)
{
    L_FUNCTION();

    raise();
    activateWindow();

    setMouseTracking(true);

    QWidget::showEvent(event);
    L_WARN("is visable = {0} && x: {1}, y: {2}, w: {3}, h: {4} @ {5} --- {6}"
        , this->isVisible(), pos().x(), pos().y(), size().width(), size().height(), m_status.toStdString().c_str()
        , __FUNCTION__);
}

void Widget::hideEvent(QHideEvent* event)
{
    setMouseTracking(false);

    resize(0, 0);

    QWidget::hideEvent(event);

    L_INFO("is visable = {0} && x: {1}, y: {2}, w: {3}, h: {4} @ {5} --- {6}"
        , this->isVisible(), pos().x(), pos().y(), size().width(), size().height(), m_status.toStdString().c_str()
        , __FUNCTION__);
}

void Widget::closeEvent(QCloseEvent* event)
{
    event->ignore();

    L_TRACE("{0} stat = {1}", __FUNCTION__, m_status.toStdString().c_str());

    hide();
}

void Widget::mousePressEvent(QMouseEvent* event)
{
    if (m_status != "giveup")
        m_workspace->onMousePress(event);
}

void Widget::mouseMoveEvent(QMouseEvent* event)
{
    L_TRACE("{0} stat = {1}", __FUNCTION__, m_status.toStdString().c_str());
    if (m_status != "giveup")
        m_workspace->onMouseMove(event);
}

void Widget::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_status != "giveup")
        m_workspace->onMouseRelease(event);
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    m_workspace->onKeyPress(event);
}

void Widget::paintEvent(QPaintEvent* event)
{
    L_FUNCTION();

    Q_UNUSED(event);
    
    QPainter painter(this);

    m_workspace->draw(painter);
}

void Widget::enterEvent(QEvent* event)
{
    L_FUNCTION();
    QWidget::enterEvent(event);
}

void Widget::leaveEvent(QEvent* event)
{
    L_FUNCTION();
//     if (m_workspace->areaConfirmed() == false)
//     {
//         m_workspace->setAreaBoundary(QRect(0,0,0,0));
//         update();
//     }

    QWidget::leaveEvent(event);
}
