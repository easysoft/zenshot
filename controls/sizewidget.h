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

#ifndef SIZEWIDGET_H
#define SIZEWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QVector>
#include <QColor>

#include "controls/sizebutton.h"

/**
 * @class : SizeWidget
 * @brief : 尺寸选择面板定义
 * @note  : 用来选择尺寸大小
 */
class SizeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SizeWidget(QWidget *parent = nullptr);

    int value() const;
    void setValue(int value);

    void setValueList(const QVector<int> &valueList);

private:
    QColor m_color;
    QVector<int> m_valueList;
    QVector<int> m_radiusList;

    int m_hGap;
    int m_itemLength;

    QVector<SizeButton*> m_btnList;

    int m_value;

    void initParams();
    void createUI();
    void initChecked();

signals:
    void sizeChanged();

private slots:
    void onItemClick(int index);

};

#endif // SIZEWIDGET_H
