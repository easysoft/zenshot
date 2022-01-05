#include <qt_windows.h>
#include <QCursor>
#include <QScreen>
#include <QApplication>
#include <QWidget>
#include <QCursor>
#include "screen/helper/windowgetter.h"


QRect WindowGetter::winGeometry(QScreen *screen,QWidget *host)
{
    ::EnableWindow((HWND)host->winId(), FALSE);

    QRect result = screen->geometry();
    QRect limit(result.x(),result.y(),result.width(),result.height());

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
        result.setRect(temp_window.left,temp_window.top,
                         temp_window.right - temp_window.left,
                         temp_window.bottom - temp_window.top);
    }


    ::EnableWindow((HWND)host->winId(), TRUE);

    return result.intersected(limit);
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
