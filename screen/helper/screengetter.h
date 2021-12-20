#ifndef SCREENGETTER_H
#define SCREENGETTER_H

#include <QList>
#include "core/screeninfo.h"

/**
 * @class : ScreenGetter
 * @brief : 屏幕相关功能定义
 * @note  : 屏幕相关功能定义
 */
class ScreenGetter
{
public:
    static QList<QList<ScreenInfo>> screenList();

};

#endif // SCREENGETTER_H
