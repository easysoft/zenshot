#include "penitemwidget.h"

#include <QPainter>

PenItemWidget::PenItemWidget(Qt::PenStyle penStyle, QWidget *parent):QLabel(parent)
{
    this->m_penStyle = penStyle;
    this->m_renderer = new PenRenderer(this,penStyle,5,5);
}

PenItemWidget::~PenItemWidget()
{
    delete m_renderer;
    m_renderer = nullptr;
}

Qt::PenStyle PenItemWidget::penStyle() const
{
    return m_penStyle;
}

void PenItemWidget::paintEvent(QPaintEvent *event)
{
    m_renderer->draw();
}
