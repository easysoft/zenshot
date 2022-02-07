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
