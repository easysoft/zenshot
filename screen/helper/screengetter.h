/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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
