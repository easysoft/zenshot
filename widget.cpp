#include "widget.h"
#include <QPainter>

Widget::Widget(ScreenList *list, QWidget *parent)
    : QWidget(parent)
{
    m_status = "unknown";
    m_workspace = new Workspace(this);
    m_workspace->start(list);

    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
    setMouseTracking(true);
    showFullScreen();

    QRect geometry = list->allBoundary(true);
    setGeometry(geometry);
}

Widget::~Widget()
{
    delete m_workspace;
    m_workspace = nullptr;
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


