#ifndef SCREENLIST_H
#define SCREENLIST_H

#include <QPainter>
#include <QRect>

#include "core/screeninfo.h"

/**
 * @class : ScreenList
 * @brief : 屏幕列表集合
 * @note  : 屏幕列表集合基本功能
 */
class ScreenList
{
public:
    ScreenList(QList<ScreenInfo> list);

    QRect allBoundary(bool isGlobal=false) const;
    QPixmap allPixMap() const;

    QRect boundaryAt(int screenIndex,bool isGlobal=false);
    QScreen *screenAt(int screenIndex);
    QPixmap pixmapAt(int screenIndex);

    int indexAtMouse();
    QRect toLocal(QRect rect);

    void draw(QPainter &painter);

private:
    QRect m_allBoundary;
    QPixmap m_allPixMap;
    QList<ScreenInfo> m_List;

    void initParams();
};

#endif // SCREENLIST_H
