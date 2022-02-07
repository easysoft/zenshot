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

#include "starter.h"
#include "screen/helper/screengetter.h"
#include "core/screeninfo.h"
#include "core/screenlist.h"

#include <QList>
#include <QApplication>
#include <QWidget>
#include <QPropertyAnimation>

Starter::Starter():QObject()
{

}

void Starter::init(QWidget *parent)
{
    m_widgets = new QList<Widget*>();

    //收集屏幕信息
    QList<QList<ScreenInfo>> screanList = ScreenGetter::screenList();

    //构造截图界面
    for(QList<ScreenInfo> list:screanList)
    {
        ScreenList *alone = new ScreenList(list);

        Widget *w = new Widget(alone,parent);
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();

        m_widgets->append(w);
        connect(w->workspace(), SIGNAL(quitShot(int)), this, SLOT(close(int)));
        connect(w->workspace(), SIGNAL(finishConfirmArea()), this, SLOT(finishConfirmArea()));
    }
}

void Starter::close(int code)
{
    QVector<Widget*> widgets = m_widgets->toVector();
    for(Widget* w:widgets)
    {
        //w->close();
        QPropertyAnimation *animation = new QPropertyAnimation(w,"windowOpacity");
        animation->setDuration(0);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
    }

    QApplication::exit(code);
}

void Starter::finishConfirmArea()
{
    QVector<Widget*> widgets = m_widgets->toVector();
    for(Widget* w:widgets)
    {
        w->finishConfirmArea();
    }
}
