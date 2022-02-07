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

#include "linebar.h"
#include "core/utils.h"

#include <QVariant>

LineBar::LineBar(Workspace *workspace) : PropsBar(workspace)
{
    createWidget();
    loadProps();
    connectEvents();
}

void LineBar::createWidget()
{
    //线宽选择组件构造添加
    m_sizeWidget = new SizeInputWidget();
    m_sizeWidget->setValue(Utils::LineWidthDefault());
    m_layout->addWidget(m_sizeWidget);

    //线条样式组件构造添加
    m_penStyleCombobox = new PenCombobox();
    m_penStyleCombobox->setProperty("forTip","penBtn");
    m_layout->addWidget(m_penStyleCombobox);

    //颜色组件构造添加
    m_colorWidget = new ColorWidget();
    m_layout->addWidget(m_colorWidget);
}

void LineBar::loadProps()
{
    int mSize = m_store->read(Utils::forLineKey(),Utils::LineWidthName(),Utils::LineWidthDefault()).toInt();
    QColor mColor = m_store->readColor(Utils::forLineKey(),Utils::LineColorName(),Utils::LineColorDefault());
    Qt::PenStyle mStyle = m_store->readPenStyle(Utils::forLineKey(),Utils::LineStyleName(),Utils::LineStyleDefault());

    m_sizeWidget->setValue(mSize);
    m_colorWidget->setSelectedColor(mColor);
    m_penStyleCombobox->setPenStyle(mStyle);
}

void LineBar::saveProps()
{
    int mSize = m_sizeWidget->value();
    QColor mColor = m_colorWidget->selectedColor();
    Qt::PenStyle mStyle = m_penStyleCombobox->penStyle();

    m_store->write(Utils::forLineKey(),Utils::LineWidthName(),mSize);
    m_store->writeColor(Utils::forLineKey(),Utils::LineColorName(),mColor);
    m_store->writePenStyle(Utils::forLineKey(),Utils::LineStyleName(),mStyle);
}

void LineBar::connectEvents()
{
    connect(m_sizeWidget, SIGNAL(sizeChanged()), this, SLOT(propsChanged()));
    connect(m_colorWidget, SIGNAL(colorChanged()), this, SLOT(propsChanged()));
    connect(m_penStyleCombobox, SIGNAL(penStyleChanged()), this, SLOT(propsChanged()));
}
