/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "screengetter.h"

#include "spdlogwrapper.hpp"

#include <QApplication>
#include <QDesktopWidget>

#define IS_CROSS_SCREEN_VER_ 0

QList<QList<ScreenInfo>> ScreenGetter::screenList()
{
    QList<ScreenInfo> tmpResults;

    int w = 0, h = 0;
    QList<QScreen*> oList = QApplication::screens();
    for(QScreen* screen:oList)
    {
        double pixelRatio = screen->devicePixelRatio();

        QRect mRect = screen->geometry();
        L_TRACE("********** mRect: {0}, {1}, {2}, {3}", mRect.left(), mRect.top(), mRect.right(), mRect.bottom());
        QPixmap mPixmap = screen->grabWindow(QApplication::desktop()->winId(),
                                             mRect.x(),
                                             mRect.y(),
                                             mRect.width()/pixelRatio,
                                             mRect.height()/pixelRatio);
        ScreenInfo info;
        info.object = screen;
        info.boundary = mRect;
        info.pixmap = mPixmap;

        tmpResults.append(info);
    }

    QList<QList<ScreenInfo>> results;
#if IS_CROSS_SCREEN_VER_
	//允许跨多屏截图
	results.append(tmpResults);
	return results;
#else
	//下面的不支持跨多屏截图
	for (ScreenInfo info : tmpResults)
	{
		QList<ScreenInfo> alone;
		alone.append(info);

		results.append(alone);
    }
#endif // IS_SINGLE_SCREEN_VER_

    return results;
}
