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

#include "curvebar.h"
#include "core/utils.h"

#include <QVariant>

CurveBar::CurveBar(Workspace *workspace) : PropsBar(workspace)
{
    createWidget();
    loadProps();
    connectEvents();
}

void CurveBar::createWidget()
{
    //线宽选择组件构造添加
    m_sizeWidget = new SizeInputWidget();
    m_sizeWidget->setValue(Utils::CurveWidthDefault());
    m_layout->addWidget(m_sizeWidget);

    //添加分割线
    //addSeperator();

    //颜色组件构造添加
    m_colorWidget = new ColorWidget();
    m_layout->addWidget(m_colorWidget);
}

void CurveBar::loadProps()
{
    int mSize = m_store->read(Utils::forCurveKey(),Utils::CurveWidthName(),Utils::CurveWidthDefault()).toInt();
    QColor mColor = m_store->readColor(Utils::forCurveKey(),Utils::CurveColorName(),Utils::CurveColorDefault());

    m_sizeWidget->setValue(mSize);
    m_colorWidget->setSelectedColor(mColor);
}

void CurveBar::saveProps()
{
    int mSize = m_sizeWidget->value();
    QColor mColor = m_colorWidget->selectedColor();

    m_store->write(Utils::forCurveKey(),Utils::CurveWidthName(),mSize);
    m_store->writeColor(Utils::forCurveKey(),Utils::CurveColorName(),mColor);
}

void CurveBar::connectEvents()
{
    connect(m_sizeWidget, SIGNAL(sizeChanged()), this, SLOT(propsChanged()));
    connect(m_colorWidget, SIGNAL(colorChanged()), this, SLOT(propsChanged()));
}
