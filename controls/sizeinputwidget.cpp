/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "sizeinputwidget.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QtMath>

SizeInputWidget::SizeInputWidget(QWidget *parent):QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground);

    m_minSize = 1;
    m_maxSize = 20;

    m_inpputBox = new QSpinBox(this);

    m_inpputBox->setSuffix("px");
    m_inpputBox->setFixedWidth(ts(60));
    m_inpputBox->setMinimum(m_minSize);
    m_inpputBox->setMaximum(m_maxSize);

    QSize mSize = m_inpputBox->size();

    float height = ts(21);
    setMinimumSize(mSize.width() + height + 2,height+2);

    m_inpputBox->move(height+1,1);

    connect(m_inpputBox, SIGNAL(valueChanged(int)), this, SLOT(onInpputIntChanged(int)));
}

int SizeInputWidget::value() const
{
    return m_inpputBox->value();
}

void SizeInputWidget::setValue(int value)
{
    m_inpputBox->setValue(value);
    update();
}

void SizeInputWidget::onInpputIntChanged(int)
{
    update();
    emit sizeChanged();
}

void SizeInputWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    QBrush brush;
    brush.setColor(QColor(244,67,54));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    QPen pen;
    pen.setColor(QColor(0,0,0,0));
    pen.setWidth(0);
    painter.setPen(pen);

    QSize mSize = size();
    int length = qMin(mSize.height()-2,m_inpputBox->value());
    QPoint center(mSize.height()/2,mSize.height()/2);

    QRect rect(center.x()-length/2,center.y()-length/2,length,length);
    painter.drawEllipse(rect);
}
