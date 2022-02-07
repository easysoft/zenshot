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

#include "pencombobox.h"

#include <QWidgetAction>

PenCombobox::PenCombobox(QWidget *parent):QPushButton(parent)
{
    setMinimumWidth(ts(62));

    m_styleList.append(Qt::SolidLine);
    m_styleList.append(Qt::DashLine);
    m_styleList.append(Qt::DotLine);
    m_styleList.append(Qt::DashDotLine);
    m_styleList.append(Qt::DashDotDotLine);

    this->m_renderer = new PenRenderer(this,Qt::SolidLine,10,25);

    m_menu = new QMenu();
    setMenu(m_menu);

    connect(m_menu, SIGNAL(aboutToShow()), this, SLOT(menuAboutToShow()));
    connect(m_menu, SIGNAL(triggered(QAction*)), this, SLOT(menuTriggered(QAction*)));

    m_menu->setStyleSheet("QLabel {padding: 3px 0 3px 0; background-color: transparent;}"
        "QLabel:hover {background-color: rgb(0, 122, 255);}");

    createSelect();
}

PenCombobox::~PenCombobox()
{
    m_styleList.clear();
    qDeleteAll(m_itemWidgetList);
    m_itemWidgetList.clear();
}

Qt::PenStyle PenCombobox::penStyle() const
{
    return m_penStyle;
}

void PenCombobox::setPenStyle(const Qt::PenStyle &style)
{
    m_penStyle = style;
    m_renderer->setPenStyle(style);
    update();
}

void PenCombobox::createSelect()
{
    foreach(Qt::PenStyle mStyle,m_styleList)
    {
        QWidgetAction* wa1 = new QWidgetAction(m_menu);
        PenItemWidget *item = new PenItemWidget(mStyle);
        wa1->setDefaultWidget(item);
        m_menu->addAction(wa1);

        m_itemWidgetList.append(item);
    }
}

void PenCombobox::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    m_renderer->draw();
}

void PenCombobox::menuAboutToShow()
{
    if(m_menu)
    {
        m_menu->setFixedWidth(this->width());
    }
}

void PenCombobox::menuTriggered(QAction *action)
{
    if(!action)
        return;

    QWidgetAction* qwa = dynamic_cast<QWidgetAction*>(action);
    if(!qwa)
        return;

    PenItemWidget* item = dynamic_cast<PenItemWidget*>(qwa->defaultWidget());
    if(!item)
        return;

    Qt::PenStyle selected = item->penStyle();

    setPenStyle(selected);

    emit penStyleChanged();
}
