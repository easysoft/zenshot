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

#include "colorwidget.h"
#include "QSignalMapper"
#include <QPainter>
#include <QBrush>

ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent)
{
    initParams();
    createUI();
}

QColor ColorWidget::selectedColor() const
{
    return m_selectedColor;
}

void ColorWidget::setSelectedColor(const QColor &selectedColor)
{
    m_selectedColor = selectedColor;
    m_selectedBtn->setContentColor(m_selectedColor);
}

void ColorWidget::initParams()
{
    m_maxColorNum = 16;

    m_hGap = 2;
    m_vGap = 2;
    m_mainGap = 4;

    m_itemLength = 11; //10
    m_itemPadding = 0;
    m_itemActivePadding = 1;

    m_itemBorderWidth = 0;
    m_itemBorderRadius = 1;
    m_itemBorderColor = QColor(255,255,255);
    m_itemBackgroundColor = QColor(255,255,255);

    m_colorList.append(QColor(242,69,61));
    m_colorList.append(QColor(80,174,85));
    m_colorList.append(QColor(3,169,244));
    m_colorList.append(QColor(63,81,181));
    m_colorList.append(QColor(103,58,183));
    m_colorList.append(QColor(156,39,176));
    m_colorList.append(QColor(233,30,99));
    m_colorList.append(QColor(51,51,51));
    m_colorList.append(QColor(255,138,128));
    m_colorList.append(QColor(105,240,174));
    m_colorList.append(QColor(238,255,65));
    m_colorList.append(QColor(140,158,255));
    m_colorList.append(QColor(179,136,255));
    m_colorList.append(QColor(234,128,252));
    m_colorList.append(QColor(255,235,59));
    m_colorList.append(QColor(255,255,255));


    m_selectedColor = m_colorList[0];
}

void ColorWidget::createUI()
{
    int colNum = m_maxColorNum/2;

    int i_itemLength = ts(m_itemLength);
    int i_vGap = ts(m_vGap);
    int i_hGap = ts(m_hGap);
    int i_mainGap = ts(m_mainGap);

    //计算整体的宽高
    int totalHeight = i_itemLength*2 + i_vGap;
    int totalWidth = colNum * i_itemLength + (colNum - 1) * i_hGap + totalHeight + i_mainGap;

    //设置组件的最小尺寸
    setMinimumSize(totalWidth,totalHeight);

    //创建选中颜色方块
    m_selectedBtn = new ColorButton(this);
    setProps(m_selectedBtn,m_itemLength*2 + m_vGap,m_itemPadding*2,m_itemPadding*2,m_selectedColor,m_itemBorderRadius*2);

    //创建色块
    QSignalMapper *mapper = new QSignalMapper(this);

    for(int i=0;i<colNum;i++)
    {
        ColorButton *colorBtn = new ColorButton(this);
        setProps(colorBtn,m_itemLength,m_itemPadding,m_itemActivePadding,m_colorList[i],m_itemBorderRadius);
        colorBtn->move(totalHeight + i_mainGap + i * (i_itemLength + i_hGap), 0);

        connect(colorBtn,SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(colorBtn,i);

        colorBtn->show();
    }

    for(int i=colNum;i<m_maxColorNum;i++)
    {
        ColorButton *colorBtn = new ColorButton(this);
        setProps(colorBtn,m_itemLength,m_itemPadding,m_itemActivePadding,m_colorList[i],m_itemBorderRadius);
        colorBtn->move(totalHeight + i_mainGap + (i-colNum) * (i_itemLength + i_hGap), i_itemLength + i_vGap);

        connect(colorBtn,SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(colorBtn,i);

        colorBtn->show();
    }

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(itemChanged(int)));
}

void ColorWidget::setProps(ColorButton *btn, int length, int padding, int activePadding, QColor cotentColor,int radius)
{
    btn->setLength(length);
    btn->setPadding(padding);
    btn->setHoverPadding(activePadding);
    btn->setBorderWidth(m_itemBorderWidth);
    btn->setBorderColor(m_itemBorderColor);
    btn->setBackgroundColor(m_itemBackgroundColor);

    btn->setBorderRadius(radius);

    btn->setContentColor(cotentColor);
}

void ColorWidget::itemChanged(int newColorIndex)
{
    QColor selected = m_colorList[newColorIndex];
    if(m_selectedColor != selected)
    {
        setSelectedColor(m_colorList[newColorIndex]);

        emit colorChanged();
    }
}
