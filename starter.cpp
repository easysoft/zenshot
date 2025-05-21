/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "starter.h"
#include "screen/helper/screengetter.h"
#include "core/screeninfo.h"
#include "core/screenlist.h"

#include "starterui.h"

#include "spdlogwrapper.hpp"

#include <QList>
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QPropertyAnimation>

#include <algorithm>

extern StarterUI* g_start_ui_;

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
    auto screanList = ScreenGetter::screenList();

    //构造截图界面
    for (int index = 0; index < screanList.size(); index++)
    {
        auto list = screanList[index];
        L_DEBUG("list size = {0}", list.size());
        std::shared_ptr<ScreenList> alone(new ScreenList(list));
        Widget* w = nullptr;
        if (m_unused_widgets->empty())
        {
            L_TRACE("++++++++++++++ new screen list & widget");
            w = new Widget(parent);
            connect(w->workspace(), SIGNAL(quitShot(int)), this, SLOT(finishShot(int)), Qt::DirectConnection);
            connect(w->workspace(), SIGNAL(finishConfirmArea()), this, SLOT(finishConfirmArea()), Qt::DirectConnection);
        }
        else
        {
            L_TRACE("============== use old screen list & widget");
            w = m_unused_widgets->back();
            m_unused_widgets->pop_back();
        }

        L_DEBUG("!!!!!!!!!!!! x = {0}, y = {1}, w = {2}, h = {3} && screen @ {4}", w->pos().x(), w->pos().y(), w->size().width(), w->size().height(), index);

        w->start(alone, index);
        m_widgets->append(w);
    }

    L_DEBUG("m_unused_widgets size: {0}, m_widgets size: {1}", m_unused_widgets->size(), m_widgets->size());
}

void Starter::cleanup()
{
    for (auto w : *m_widgets)
    {
        w->cleanup();
    }
}

void Starter::rasie()
{
    for (auto w : *m_widgets)
    {
        w->raise();
        w->activateWindow();
    }
}

void Starter::finishShot(int code)
{
    (void)code;
    L_FUNCTION();
    for (auto w : *m_widgets)
    {
        w->hide();
    }

    emit ShotDone(this);

    if (m_bExit)
    {
        g_start_ui_->close();
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
