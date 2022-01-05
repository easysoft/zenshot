#include "screengetter.h"

#include <QApplication>
#include <QDesktopWidget>

QList<QList<ScreenInfo>> ScreenGetter::screenList()
{
    QList<ScreenInfo> tmpResults;

    QList<QScreen*> oList = QApplication::screens();
    for(QScreen* screen:oList)
    {
        double pixelRatio = screen->devicePixelRatio();

        QRect mRect = screen->geometry();
        QPixmap mPixmap = screen->grabWindow(0,
                                             mRect.x(),
                                             mRect.y(),
                                             mRect.width(),
                                             mRect.height());
        mPixmap.setDevicePixelRatio(pixelRatio);

        ScreenInfo info;
        info.object = screen;
        info.boundary = mRect;
        info.pixmap = mPixmap;

        tmpResults.append(info);
    }

    QList<QList<ScreenInfo>> results;

    for(ScreenInfo info:tmpResults)
    {
        QList<ScreenInfo> alone;
        alone.append(info);

        results.append(alone);
    }

    return results;
}

