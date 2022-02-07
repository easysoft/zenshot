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
