#include "ellipsebar.h"
#include "core/utils.h"

#include <QVariant>

EllipseBar::EllipseBar(Workspace *workspace) : PropsBar(workspace)
{
    createWidget();
    loadProps();
    connectEvents();
}

void EllipseBar::createWidget()
{
    //线宽选择组件构造添加
    m_sizeWidget = new SizeInputWidget();
    m_sizeWidget->setValue(Utils::EllipseWidthDefault());
    m_layout->addWidget(m_sizeWidget);

    //线条样式组件构造添加
    m_penStyleCombobox = new PenCombobox();
    m_layout->addWidget(m_penStyleCombobox);

    //颜色组件构造添加
    m_colorWidget = new ColorWidget();
    m_layout->addWidget(m_colorWidget);
}

void EllipseBar::loadProps()
{
    int mSize = m_store->read(Utils::forEllipseKey(),Utils::EllipseWidthName(),Utils::EllipseWidthDefault()).toInt();
    QColor mColor = m_store->readColor(Utils::forEllipseKey(),Utils::EllipseColorName(),Utils::EllipseColorDefault());
    Qt::PenStyle mStyle = m_store->readPenStyle(Utils::forEllipseKey(),Utils::EllipseStyleName(),Utils::EllipseStyleDefault());

    m_sizeWidget->setValue(mSize);
    m_colorWidget->setSelectedColor(mColor);
    m_penStyleCombobox->setPenStyle(mStyle);
}

void EllipseBar::saveProps()
{
    int mSize = m_sizeWidget->value();
    QColor mColor = m_colorWidget->selectedColor();
    Qt::PenStyle mStyle = m_penStyleCombobox->penStyle();

    m_store->write(Utils::forEllipseKey(),Utils::EllipseWidthName(),mSize);
    m_store->writeColor(Utils::forEllipseKey(),Utils::EllipseColorName(),mColor);
    m_store->writePenStyle(Utils::forEllipseKey(),Utils::EllipseStyleName(),mStyle);
}

void EllipseBar::connectEvents()
{
    connect(m_sizeWidget, SIGNAL(sizeChanged()), this, SLOT(propsChanged()));
    connect(m_colorWidget, SIGNAL(colorChanged()), this, SLOT(propsChanged()));
    connect(m_penStyleCombobox, SIGNAL(penStyleChanged()), this, SLOT(propsChanged()));
}
