#include "penrenderer.h"

#include <QPainter>

PenRenderer::PenRenderer(QWidget *widget,Qt::PenStyle penStyle, int marginLeft,int marginRight)
{
    this->m_widget = widget;
    this->m_marginLeft = marginLeft;
    this->m_marginRight = marginRight;

    this->m_penStyle = penStyle;
    this->m_lineWidth = 2;
    this->m_lineColor = QColor(128,128,128);
}

Qt::PenStyle PenRenderer::penStyle() const
{
    return m_penStyle;
}

void PenRenderer::setPenStyle(const Qt::PenStyle &lineStyle)
{
    m_penStyle = lineStyle;
}

void PenRenderer::draw()
{
    QPainter painter(m_widget);

    painter.save();

    QSize size = m_widget->size();
    QPoint p1(m_marginLeft,size.height()/2);
    QPoint p2(size.width()-m_marginRight,size.height()/2);

    QPen pen;
    pen.setColor(m_lineColor);
    pen.setWidth(m_lineWidth);
    pen.setStyle(m_penStyle);

    painter.setPen(pen);
    painter.drawLine(p1,p2);

    painter.restore();
}







