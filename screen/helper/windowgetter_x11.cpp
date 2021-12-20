#include "screen/helper/windowgetter.h"

//#include<QCursor>
#include <QScreen>
#include <QApplication>
#include <QWidget>

#include <QLibrary>
#include <QtX11Extras/QX11Info>
#include <X11/Xutil.h>
#include <X11/Xlib.h>

typedef QList<WId> WindowList;

struct WND_INFO{
    WId id;
    QRect pos;
};

static WindowList getWindowIdList(Atom prop)
{
    WindowList res;
    Atom type = 0;
    int format = 0;
    uchar* data = 0;
    ulong count, after;
    Display* display = QX11Info::display();
    Window window = QX11Info::appRootWindow();
    if (XGetWindowProperty(display, window, prop, 0, 1024 * sizeof(Window) / 4, False, AnyPropertyType,
                           &type, &format, &count, &after, &data) == Success)
    {
        Window* list = reinterpret_cast<Window*>(data);
        for (uint i = 0; i < count; ++i)
            res += list[i];
        if (data)
            XFree(data);
    }
    return res;
}

QRect getWindowGeometry(WId window)
{
    int x, y;
    uint width, height, border, depth;
    Window root, child;
    Display* display = QX11Info::display();
    XGetGeometry(display, window, &root, &x, &y, &width, &height, &border, &depth);
    XTranslateCoordinates(display, window, root, x, y, &x, &y, &child);

    static Atom net_frame = 0;
    if (!net_frame)
        net_frame = XInternAtom(QX11Info::display(), "_NET_FRAME_EXTENTS", True);

    QRect rect(x, y, width, height);
    Atom type = 0;
    int format = 0;
    uchar* data = 0;
    ulong count, after;
    if (XGetWindowProperty(display, window, net_frame, 0, 4, False, AnyPropertyType,
                           &type, &format, &count, &after, &data) == Success)
    {
        // _NET_FRAME_EXTENTS, left, right, top, bottom, CARDINAL[4]/32
        if (count == 4)
        {
            long* extents = reinterpret_cast<long*>(data);
            rect.adjust(-extents[0], -extents[2], extents[1], extents[3]);
        }
        if (data)
            XFree(data);
    }
    return rect;
}

QList<WND_INFO> getWindowInfoList()
{
    static Atom net_clients = 0;
    if (!net_clients)
        net_clients = XInternAtom(QX11Info::display(), "_NET_CLIENT_LIST_STACKING", True);

    WindowList idList = getWindowIdList(net_clients);

    QList<WND_INFO> infoList;
    for(int i=0;i<idList.size();i++)
    {
        WND_INFO info;
        info.id = idList[i];
        info.pos = getWindowGeometry(idList[i]);

        infoList.push_back(info);
    }

    return infoList;
}

static QList<WND_INFO> windowList;

QRect WindowGetter::winGeometry(QScreen *screen,QWidget *host)
{
    if(windowList.count() == 0)
           windowList = getWindowInfoList();

    QPoint mouse = QCursor::pos();

    for(int i=windowList.size()-1;i>=0;i--)
    {
        WND_INFO info = windowList[i];
        if(info.pos.contains(mouse))
            return info.pos;
    }

    return screen->geometry();
}
