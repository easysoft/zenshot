#include "starter.h"
#include "screen/helper/screengetter.h"
#include "core/screeninfo.h"
#include "core/screenlist.h"

#include <QList>
#include <QApplication>

Starter::Starter():QObject()
{

}

void Starter::init()
{
    m_widgets = new QList<Widget*>();

    //收集屏幕信息
    QList<QList<ScreenInfo>> screanList = ScreenGetter::screenList();

    //构造截图界面
    for(QList<ScreenInfo> list:screanList)
    {
        ScreenList *alone = new ScreenList(list);

        Widget *w = new Widget(alone);
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
