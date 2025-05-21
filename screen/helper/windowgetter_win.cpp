/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include <qt_windows.h>
#include <QCursor>
#include <QScreen>
#include <QApplication>
#include <QWidget>
#include <QCursor>
#include "screen/helper/windowgetter.h"

#include "spdlogwrapper.hpp"

QRect WindowGetter::winGeometry(QScreen *screen,QWidget *host)
{
	::EnableWindow((HWND)host->winId(), FALSE);

	QRect result = screen->geometry();
	L_INFO("!!! [[[[[[[ result @ {0}, {1}, {2}, {3} ]]]]]]]", result.left(), result.top(), result.right(), result.bottom());
	QRect limit(result.x(), result.y(), result.width(), result.height());

	HWND hwnd;
	POINT pt;
	// 获得当前鼠标位置
	::GetCursorPos(&pt);
	// 获得当前位置桌面上的子窗口
	hwnd = ::ChildWindowFromPointEx(::GetDesktopWindow(),
		pt, CWP_SKIPDISABLED | CWP_SKIPINVISIBLE | CWP_SKIPTRANSPARENT);
	if (hwnd != NULL) {
		RECT temp_window;
		::GetWindowRect(hwnd, &temp_window);
		L_INFO("]]]]]]] temp_window @ {0}, {1}, {2}, {3} [[[[[[[", temp_window.left, temp_window.top, temp_window.right, temp_window.bottom);
		result.setRect(temp_window.left, temp_window.top,
			temp_window.right - temp_window.left,
			temp_window.bottom - temp_window.top);
	}

	::EnableWindow((HWND)host->winId(), TRUE);

	result = result.intersected(limit);
	L_INFO("### [[[[[[[ result @ {0}, {1}, {2}, {3} ]]]]]]]", result.left(), result.top(), result.right(), result.bottom());
	return result;
}

/*
QRect Screensnap::winGeometry(QScreen *screen,QWidget *host)
{
    ::EnableWindow((HWND)host->winId(), FALSE);

    QRect result = screen->geometry();

    HWND hwnd;
    POINT pt;
    // 获得当前鼠标位置
    ::GetCursorPos(&pt);
    // 获得当前位置桌面上的子窗口
    hwnd = ::ChildWindowFromPointEx(::GetDesktopWindow(),
                        pt, CWP_SKIPDISABLED | CWP_SKIPINVISIBLE);
    if (hwnd != NULL) {
        HWND temp_hwnd;
        temp_hwnd = hwnd;
        while (true) {
            ::GetCursorPos(&pt);
            ::ScreenToClient(temp_hwnd, &pt);
            temp_hwnd = ::ChildWindowFromPointEx(temp_hwnd,
                                     pt, CWP_SKIPINVISIBLE);
            if (temp_hwnd == NULL || temp_hwnd == hwnd)
                break;
            hwnd = temp_hwnd;
        }
        RECT temp_window;
        ::GetWindowRect(hwnd, &temp_window);
        result.setRect(temp_window.left,temp_window.top,
                         temp_window.right - temp_window.left,
                         temp_window.bottom - temp_window.top);
    }


    ::EnableWindow((HWND)host->winId(), TRUE);

    return result;
}
*/
