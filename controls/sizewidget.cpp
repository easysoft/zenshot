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

#include "sizewidget.h"
#include <QtMath>
#include <QVariant>

SizeWidget::SizeWidget(QWidget *parent) : QWidget(parent)
{
    initParams();
    createUI();
}

int SizeWidget::value() const
{
    return m_value;
}

void SizeWidget::setValue(int value)
{
    m_value = value;

    initChecked();
}

void SizeWidget::setValueList(const QVector<int> &valueList)
{
    m_valueList = valueList;

    int count = qMin(m_valueList.count(),m_radiusList.count());
    for(int i=0;i<count;i++)
    {
        m_btnList[i]->setValue(m_valueList[i]);
    }

    initChecked();
}

void SizeWidget::initParams()
{
    m_hGap = 2;
    m_itemLength = 34;
    m_color = QColor(47,141,221,100);

    m_valueList.append(1);
    m_valueList.append(2);
    m_valueList.append(4);

    m_radiusList.append(2);
    m_radiusList.append(4);
    m_radiusList.append(8);

    if(m_valueList.count() > 0)
        m_value = m_valueList[0];
}

void SizeWidget::createUI()
{
    QButtonGroup *group = new QButtonGroup(this);

    int count = qMin(m_valueList.count(),m_radiusList.count());

    for(int i=0;i<count;i++)
    {
        SizeButton *btn = new SizeButton(this);
        btn->setCheckable(true);
        btn->setAutoExclusive(true);
        btn->setColor(m_color);
        btn->setValue(m_valueList[i]);
        btn->setRadius(m_radiusList[i]);

        btn->setGeometry((m_itemLength+m_hGap)*i,0,m_itemLength,m_itemLength);

        group->addButton(btn,i);
        m_btnList.append(btn);

        btn->setProperty("forTip","thickness");
        btn->show();
    }

    group->setExclusive(true);
    connect(group,SIGNAL(buttonClicked(int)),this,SLOT(onItemClick(int)));

    initChecked();

    setMinimumSize(count * m_itemLength + (count-1)*m_hGap,m_itemLength);
}

void SizeWidget::initChecked()
{
    foreach(SizeButton* btn,m_btnList)
    {
        btn->setChecked(false);

        if(btn->value() == m_value)
        {
            btn->setChecked(true);
            break;
        }
    }
}

void SizeWidget::onItemClick(int index)
{
    int selected = m_valueList[index];
    if(selected != m_value)
    {
        m_value = selected;
        emit sizeChanged();
    }
}
