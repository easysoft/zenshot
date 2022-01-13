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
