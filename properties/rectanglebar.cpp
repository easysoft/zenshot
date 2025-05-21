/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
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

