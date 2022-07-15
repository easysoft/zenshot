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

#include "spdlogwrapper.hpp"

#include <QList>
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QPropertyAnimation>

#include <algorithm>

Starter::Starter()
    : QObject()
    , m_widgets(new QList<Widget*>)
{
}

Starter::~Starter()
{
    L_TRACE("{0} @ {1}", __FUNCTION__, __LINE__);
}

void Starter::init(QWidget *parent)
{
    QList<Widget*> widgets = std::move(*m_widgets);
    //收集屏幕信息
    QList<QList<ScreenInfo>> screanList = ScreenGetter::screenList();

    //构造截图界面
    std::for_each(screanList.begin(), screanList.end(), [&](const QList<ScreenInfo>& list)
        {
            if (widgets.empty()) 
            {
                ScreenList* alone = new ScreenList(list);

                Widget* w = new Widget(alone, parent);
                w->show();

                m_widgets->append(w);
                connect(w->workspace(), SIGNAL(quitShot(int)), this, SLOT(finishShot(int)), Qt::DirectConnection);
                connect(w->workspace(), SIGNAL(finishConfirmArea()), this, SLOT(finishConfirmArea()), Qt::DirectConnection);
                return;
            }

            m_widgets->append(widgets.back());
            widgets.pop_back();
        });

    L_TRACE("{0} @ {1}", __FUNCTION__, time(0));
}

void Starter::finishShot(int code)
{
#ifdef Q_OS_WIN32
    (void*)code;
#endif // Q_OS_WIN32
    L_TRACE("{0} @ {1}", __FUNCTION__, time(0));
    for(auto w : *m_widgets)
    {
        //w->close();
        w->setVisible(false);

        QPropertyAnimation *animation = new QPropertyAnimation(w,"windowOpacity");
        animation->setDuration(0);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
    }

#ifdef Q_OS_WIN32
    emit ShotDone(this);
#else
    QApplication::exit(code);
#endif // Q_OS_WIN32
}

void Starter::finishConfirmArea()
{
    L_TRACE("{0} @ {1}", __FUNCTION__, time(0));
    for (auto w : *m_widgets)
    {
        w->finishConfirmArea();
    }
}
