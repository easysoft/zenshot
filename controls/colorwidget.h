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

#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QVector>
#include <QColor>

#include "controls/colorbutton.h"
#include "core/gscale.h"

/**
 * @class : ColorWidget
 * @brief : 颜色选择面板定义
 * @note  : 用来选择颜色
 */
class ColorWidget : public QWidget,GScale
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = nullptr);

    QColor selectedColor() const;
    void setSelectedColor(const QColor &selectedColor);

private:
    int m_maxColorNum;
    QColor m_selectedColor;
    QVector<QColor> m_colorList;

    int m_hGap;
    int m_vGap;
    int m_mainGap;

    int m_itemLength;
    int m_itemPadding;
    int m_itemActivePadding;

    int m_itemBorderWidth;
    int m_itemBorderRadius;
    QColor m_itemBorderColor;
    QColor m_itemBackgroundColor;

    ColorButton *m_selectedBtn;

    void initParams();
    void createUI();
    void setProps(ColorButton *btn,int length,int padding,int activePadding,QColor cotentColor,int radius);

private slots:
    void itemChanged(int newColorIndex);

signals:
    void colorChanged();
};

#endif // COLORWIDGET_H
