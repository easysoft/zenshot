/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
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
