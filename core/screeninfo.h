#ifndef SCREENINFO_H
#define SCREENINFO_H

#include <QScreen>
#include <QPixmap>
#include <QRect>

struct ScreenInfo{
    QScreen *object;
    QRect boundary;
    QPixmap pixmap;
};

#endif // SCREENINFO_H
