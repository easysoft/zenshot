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

Starter::Starter(bool exit_process)
    : QObject()
    , m_widgets(new QList<Widget*>)
    , m_unused_widgets(new QList<Widget*>)
    , m_bExit(exit_process)
{
}

Starter::~Starter()
{
    L_FUNCTION();
}

void Starter::init(QWidget* parent)
{
    L_FUNCTION();
    std::copy(m_widgets->begin(), m_widgets->end(), std::back_inserter(*m_unused_widgets));
    m_widgets->clear();

    //收集屏幕信息
    QList<QList<ScreenInfo>> screanList = ScreenGetter::screenList();

    //构造截图界面
    std::for_each(screanList.begin(), screanList.end(), [&](const QList<ScreenInfo>& list)
        {
            std::shared_ptr<ScreenList> alone(new ScreenList(list));
            Widget* w = nullptr;
            if (m_unused_widgets->empty())
            {
                L_TRACE("++++++++++++++ new screen list & widget");
                QString title;
                title.append("Widget =>>>>>>>>> ").append(std::to_string(m_widgets->size()).c_str());
                w = new Widget(parent);
                w->setWindowTitle(title);
                connect(w->workspace(), SIGNAL(quitShot(int)), this, SLOT(finishShot(int)), Qt::DirectConnection);
                connect(w->workspace(), SIGNAL(finishConfirmArea()), this, SLOT(finishConfirmArea()), Qt::DirectConnection);
            }
            else
            {
                L_TRACE("============== use old screen list & widget");
                w = m_unused_widgets->back();
                m_unused_widgets->pop_back();
            }

            w->start(alone);
            w->showFullScreen();

            w->raise();
            w->activateWindow();

            m_widgets->append(w);
        });

    L_DEBUG("m_unused_widgets size: {0}, m_widgets size: {1}", m_unused_widgets->size(), m_widgets->size());
}

void Starter::cleanup()
{
    for (auto w : *m_widgets)
    {
        w->cleanup();
    }
}

void Starter::finishShot(int code)
{
    L_FUNCTION();
    for (auto w : *m_widgets)
    {
        w->hide();
    }

    emit ShotDone(this);

    if (m_bExit)
    {
        QApplication::exit(code);
    }
}

void Starter::finishConfirmArea()
{
    L_FUNCTION();
    for (auto w : *m_widgets)
    {
        w->finishConfirmArea();
    }
}
