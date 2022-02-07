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

#include "colorbutton.h"
#include <QtMath>
#include <QPainter>

ColorButton::ColorButton(QWidget *parent) : QAbstractButton(parent)
{

    m_length = 16;

    m_isHover = false;
    m_borderWidth = 1;

    m_borderPen.setColor(m_borderColor);
    m_borderPen.setWidth(m_borderWidth);

    m_backgrondBrush.setColor(m_backgroundColor);
    m_backgrondBrush.setStyle(Qt::SolidPattern);

    m_contentBrush.setColor(m_contentColor);
    m_contentBrush.setStyle(Qt::SolidPattern);

    resize(ts(m_length),ts(m_length));
}

int ColorButton::length() const
{
    return m_length;
}

void ColorButton::setLength(int length)
{
    m_length = qMax(length,2);

    resize(ts(m_length),ts(m_length));

    update();
}

int ColorButton::padding() const
{
    return m_padding;
}

void ColorButton::setPadding(int padding)
{
    m_padding = padding;

    update();
}

int ColorButton::hoverPadding() const
{
    return m_hoverPadding;
}

void ColorButton::setHoverPadding(int activePadding)
{
    m_hoverPadding = activePadding;

    update();
}

QColor ColorButton::borderColor() const
{
    return m_borderColor;
}

void ColorButton::setBorderColor(const QColor &borderColor)
{
    m_borderColor = borderColor;
    m_borderPen.setColor(m_borderColor);

    update();
}

QColor ColorButton::contentColor() const
{
    return m_contentColor;
}

void ColorButton::setContentColor(const QColor &contentColor)
{
    m_contentColor = contentColor;
    m_contentBrush.setColor(m_contentColor);

    update();
}

QColor ColorButton::backgroundColor() const
{
    return m_backgroundColor;
}

void ColorButton::setBackgroundColor(const QColor &backgroundColor)
{
    m_backgroundColor = backgroundColor;
    m_backgrondBrush.setColor(m_backgroundColor);

    update();
}

int ColorButton::borderWidth() const
{
    return m_borderWidth;
}

void ColorButton::setBorderWidth(int borderWidth)
{
    m_borderWidth = qMax(borderWidth,0);
    m_borderPen.setWidth(m_borderWidth);

    update();
}

int ColorButton::borderRadius() const
{
    return m_borderRadius;
}

void ColorButton::setBorderRadius(int borderRadius)
{
    m_borderRadius = borderRadius;
    update();
}

void ColorButton::enterEvent(QEvent *event)
{
    m_isHover = true;

    update();
}

void ColorButton::leaveEvent(QEvent *event)
{
    m_isHover = false;

    update();
}

void ColorButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    float i_borderWidth = ts(m_borderWidth);
    float i_length = ts(m_length);
    float i_padding = ts(m_padding);
    float i_hoverPadding = ts(m_hoverPadding);

    QRectF borderRect(i_borderWidth/2,
                      i_borderWidth/2,
                      i_length-m_borderWidth,
                      i_length-m_borderWidth);

    QRectF contentRect(i_padding + i_borderWidth,
                      i_padding + i_borderWidth,
                      i_length - (i_padding + i_borderWidth)*2,
                      i_length - (i_padding + i_borderWidth)*2);
    if(m_isHover == true)
    {
        contentRect.setRect(i_hoverPadding + i_borderWidth,
                            i_hoverPadding + i_borderWidth,
                            i_length -(i_hoverPadding + i_borderWidth)*2,
                            i_length - (i_hoverPadding + i_borderWidth)*2);
    }

    painter.setPen(m_borderPen);

    painter.setBrush(m_backgrondBrush);
    painter.drawRoundedRect(borderRect,ts(m_borderRadius),ts(m_borderRadius));

    m_borderPen.setWidth(0);
    painter.setPen(m_borderPen);
    painter.setBrush(m_contentBrush);
    painter.drawRoundedRect(contentRect,ts(0),ts(0));

}
