/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include <gtk/gtk.h>

#include "screen/helper/windowgetter.h"

#include "spdlogwrapper.hpp"

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

static GdkWindow *
screenshot_find_active_window (void)
{
  GdkWindow *window;
  GdkScreen *default_screen;

  default_screen = gdk_screen_get_default ();
  window = gdk_screen_get_active_window (default_screen);

  return window;
}

static gboolean
screenshot_window_is_desktop (GdkWindow *window)
{
  GdkWindow *root_window = gdk_get_default_root_window ();
  GdkWindowTypeHint window_type_hint;

  if (window == root_window)
    return TRUE;

  window_type_hint = gdk_window_get_type_hint (window);
  if (window_type_hint == GDK_WINDOW_TYPE_HINT_DESKTOP)
    return TRUE;

  return FALSE;
}

GdkWindow *
do_find_current_window (void)
{
  GdkWindow *current_window;
  GdkDeviceManager *manager;
  GdkDevice *device;

  current_window = screenshot_find_active_window ();
  manager = gdk_display_get_device_manager (gdk_display_get_default ());
  device = gdk_device_manager_get_client_pointer (manager);
  
  /* If there's no active window, we fall back to returning the
   * window that the cursor is in.
   */
  if (!current_window)
    current_window = gdk_device_get_window_at_position (device, NULL, NULL);

  if (current_window)
    {
      if (screenshot_window_is_desktop (current_window))
	/* if the current window is the desktop (e.g. nautilus), we
	 * return NULL, as getting the whole screen makes more sense.
         */
        return NULL;

      /* Once we have a window, we take the toplevel ancestor. */
      current_window = gdk_window_get_toplevel (current_window);
    }

  return current_window;
}

static void
screenshot_fallback_get_window_rect_coords (GdkWindow *window,
                                            gboolean include_border,
                                            GdkRectangle *real_coordinates_out,
                                            GdkRectangle *screenshot_coordinates_out)
{
  gint x_orig, y_orig;
  gint width, height;
  GdkRectangle real_coordinates;

  if (include_border)
    {
      gdk_window_get_frame_extents (window, &real_coordinates);
    }
  else
    {
      real_coordinates.width = gdk_window_get_width (window);
      real_coordinates.height = gdk_window_get_height (window);
      
      gdk_window_get_origin (window, &real_coordinates.x, &real_coordinates.y);
    }

  x_orig = real_coordinates.x;
  y_orig = real_coordinates.y;
  width  = real_coordinates.width;
  height = real_coordinates.height;

  if (real_coordinates_out != NULL)
    *real_coordinates_out = real_coordinates;

  if (x_orig < 0)
    {
      width = width + x_orig;
      x_orig = 0;
    }

  if (y_orig < 0)
    {
      height = height + y_orig;
      y_orig = 0;
    }

  if (x_orig + width > gdk_screen_width ())
    width = gdk_screen_width () - x_orig;

  if (y_orig + height > gdk_screen_height ())
    height = gdk_screen_height () - y_orig;

  if (screenshot_coordinates_out != NULL)
    {
      screenshot_coordinates_out->x = x_orig;
      screenshot_coordinates_out->y = y_orig;
      screenshot_coordinates_out->width = width;
      screenshot_coordinates_out->height = height;
    }
}

static GList*
do_find_all_window (void)
{
  GdkScreen* screen = gdk_display_get_default_screen(gdk_display_get_default ());
  if (screen)
  {
    return gdk_screen_get_window_stack(screen);
  }

  return NULL;
}

static WindowList getWindowIdList(Atom prop)
{
    WindowList res;
    Atom type = 0;
    int format = 0;
    uchar* data = 0;
    ulong count, after;
    Display* display = QX11Info::display();
    Window window = QX11Info::appRootWindow();
    XWindowAttributes attrs;
    XGetWindowAttributes(display, window, &attrs);

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
  QList<WND_INFO> wnd_list;
  WND_INFO info;
  GdkWindow* window;
  GList* gl_item = NULL, *gl = NULL;
  GdkRectangle real_coordinates, screenshot_coordinates;
  
  gl = do_find_all_window();
  if (!gl)
  {
    return wnd_list;
  }
  
  for (gl_item = g_list_first(gl); gl_item; gl_item = gl_item->next)
  {
    window = (GdkWindow*)gl_item->data;
    if (screenshot_window_is_desktop(window))
    {
      continue;
    }

    screenshot_fallback_get_window_rect_coords(window, false, &real_coordinates, &screenshot_coordinates);
    
    info.pos.setX(real_coordinates.x);
    info.pos.setY(real_coordinates.y);
    info.pos.setWidth(real_coordinates.width);
    info.pos.setHeight(real_coordinates.height);

    wnd_list.push_back(info);

    g_object_unref(window);
  }
  g_list_free(gl);

  return wnd_list;
}

static QList<WND_INFO> windowList;

QRect WindowGetter::winGeometry(QScreen *screen, QWidget *host)
{
  (void)host;
  windowList = getWindowInfoList();

  std::sort(windowList.begin(), windowList.end(), [](const WND_INFO& l, const WND_INFO& r)
  {
    return l.pos.width() > r.pos.width() && l.pos.height() > r.pos.height();
  });

  QPoint mouse = QCursor::pos();

  for(int i=windowList.size()-1;i>=0;i--)
  {
    WND_INFO info = windowList[i];
    if(info.pos.contains(mouse))
        return info.pos;
  }

  return screen->geometry();
}
