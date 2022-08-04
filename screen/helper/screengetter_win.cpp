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
