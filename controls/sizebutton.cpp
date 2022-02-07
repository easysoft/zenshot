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

#include "sizebutton.h"
#include <QtMath>
#include <QPainter>
#include <QPen>


SizeButton::SizeButton(QWidget *parent) : QAbstractButton(parent)
{
    m_padding = 3;

    m_color = QColor(47,141,221,100);

    m_isHovered = false;

    m_borderWidth = 1;
    m_borderColor = QColor(255,255,255,0);
    m_backgroundColor = QColor(255,255,255,0);

    m_hovered_borderWidth = 1;
    m_hovered_borderColor = QColor(157,159,160);
    m_hovered_backgroundColor = QColor(222,225,232);

    m_checked_borderWidth = 1;
    m_checked_borderColor = QColor(157,159,160);
    m_checked_backgroundColor = QColor(222,225,232);
}

QColor SizeButton::color() const
{
    return m_color;
}

void SizeButton::setColor(const QColor &color)
{
    m_color = color;

    update();
}

int SizeButton::radius() const
{
    return m_radius;
}

void SizeButton::setRadius(int diameter)
{
    m_radius = diameter;

    update();
}

int SizeButton::value() const
{
    return m_value;
}

void SizeButton::setValue(int value)
{
    m_value = value;
}

void SizeButton::paintEvent(QPaintEvent *event)
{
    QSize mSize = size();


    QPainter painter(this);

    painter.save();

    QPen borderPen;
    borderPen.setColor(m_borderColor);
    borderPen.setWidth(m_borderWidth);

    QBrush backgroundBrush;
    backgroundBrush.setColor(m_backgroundColor);
    backgroundBrush.setStyle(Qt::SolidPattern);

    if(isChecked() == true)
    {
        borderPen.setColor(m_checked_borderColor);
        borderPen.setWidth(m_checked_borderWidth);

        backgroundBrush.setColor(m_checked_backgroundColor);
    }
    else if(m_isHovered == true)
    {
        borderPen.setColor(m_hovered_borderColor);
        borderPen.setWidth(m_hovered_borderWidth);

        backgroundBrush.setColor(m_hovered_backgroundColor);
    }

    int padding = m_padding + borderPen.width();

    QRect rect(padding,padding,mSize.width()-padding*2,mSize.width()-padding*2);

    painter.setPen(borderPen);

    painter.fillRect(rect,backgroundBrush);
    painter.drawRect(rect);


    QPoint center(mSize.width()/2,mSize.height()/2);
    int drawRadius =qMax(1, qMin(m_radius,qMin(mSize.width(),mSize.height())));

    QPen pen(QColor(0,0,0,0));
    QBrush brush(m_color,Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawEllipse(center,drawRadius,drawRadius);

    painter.restore();


}

void SizeButton::enterEvent(QEvent *event)
{
    m_isHovered = true;
    update();
}

void SizeButton::leaveEvent(QEvent *event)
{
    m_isHovered = false;
    update();
}
