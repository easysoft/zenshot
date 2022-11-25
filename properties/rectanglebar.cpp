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

#include "rectanglebar.h"
#include "core/utils.h"

#include "spdlogwrapper.hpp"

#include <QVariant>
#include <QVector>

RectangleBar::RectangleBar(Workspace *workspace) : PropsBar(workspace)
{
   createWidget();
   loadProps();
   connectEvents();
}

void RectangleBar::createWidget()
{
    //线宽选择组件构造添加
    m_sizeWidget = new SizeInputWidget();
    m_sizeWidget->setValue(Utils::RectWidthDefault());
    m_layout->addWidget(m_sizeWidget);

    //线条样式组件构造添加
    m_penStyleCombobox = new PenCombobox();
    m_layout->addWidget(m_penStyleCombobox);

    //颜色组件构造添加
    m_colorWidget = new ColorWidget();
    m_layout->addWidget(m_colorWidget);
}

void RectangleBar::loadProps()
{
    int mSize = m_store->read(Utils::forRectKey(),Utils::RectWidthName(),Utils::RectWidthDefault()).toInt();
    QColor mColor = m_store->readColor(Utils::forRectKey(),Utils::RectColorName(),Utils::RectColorDefault());
    Qt::PenStyle mStyle = m_store->readPenStyle(Utils::forRectKey(),Utils::RectStyleName(),Utils::RectStyleDefault());

    L_DEBUG("{0} @ {1}, mSize: {2}, mStyle: {3}", __FUNCTION__, __LINE__, mSize, mStyle);

    m_sizeWidget->setValue(mSize);
    m_colorWidget->setSelectedColor(mColor);
    m_penStyleCombobox->setPenStyle(mStyle);
}

void RectangleBar::saveProps()
{
    int mSize = m_sizeWidget->value();
    QColor mColor = m_colorWidget->selectedColor();
    Qt::PenStyle mStyle = m_penStyleCombobox->penStyle();

    L_DEBUG("{0} @ {1}, mSize: {2}, mStyle: {3}", __FUNCTION__, __LINE__, mSize, mStyle);

    m_store->write(Utils::forRectKey(),Utils::RectWidthName(),mSize);
    m_store->writeColor(Utils::forRectKey(),Utils::RectColorName(),mColor);
    m_store->writePenStyle(Utils::forRectKey(),Utils::RectStyleName(),mStyle);
}

void RectangleBar::connectEvents()
{
    connect(m_sizeWidget, SIGNAL(sizeChanged()), this, SLOT(propsChanged()));
    connect(m_colorWidget, SIGNAL(colorChanged()), this, SLOT(propsChanged()));
    connect(m_penStyleCombobox, SIGNAL(penStyleChanged()), this, SLOT(propsChanged()));
}

