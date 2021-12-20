#include "arrowbar.h"
#include "core/utils.h"

#include <QVariant>

ArrowBar::ArrowBar(Workspace *workspace) : PropsBar(workspace)
{
    createWidget();
    loadProps();
    connectEvents();
}

void ArrowBar::createWidget()
{
    //线宽选择组件构造添加
    m_sizeWidget = new SizeInputWidget();
    m_sizeWidget->setValue(Utils::ArrowWidthDefault());
    m_layout->addWidget(m_sizeWidget);

    //添加分割线
   // addSeperator();

    //颜色组件构造添加
    m_colorWidget = new ColorWidget();
    m_layout->addWidget(m_colorWidget);
}

void ArrowBar::loadProps()
{
  int mSize = m_store->read(Utils::forArrowKey(),Utils::ArrowWidthName(),Utils::ArrowWidthDefault()).toInt();
  QColor mColor = m_store->readColor(Utils::forArrowKey(),Utils::ArrowColorName(),Utils::ArrowColorDefault());

  m_sizeWidget->setValue(mSize);
  m_colorWidget->setSelectedColor(mColor);
}

void ArrowBar::saveProps()
{
    int mSize = m_sizeWidget->value();
    QColor mColor = m_colorWidget->selectedColor();

    m_store->write(Utils::forArrowKey(),Utils::ArrowWidthName(),mSize);
    m_store->writeColor(Utils::forArrowKey(),Utils::ArrowColorName(),mColor);
}

void ArrowBar::connectEvents()
{
    connect(m_sizeWidget, SIGNAL(sizeChanged()), this, SLOT(propsChanged()));
    connect(m_colorWidget, SIGNAL(colorChanged()), this, SLOT(propsChanged()));
}
