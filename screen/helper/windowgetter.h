/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef SCREENSNAP_H
#define SCREENSNAP_H

#include <QPixmap>
#include <QRect>
#include <QPoint>
#include <QScreen>


/**
 * @class : WindowGetter
 * @brief : 窗口智能感知相关功能定义
 * @note  : 窗口智能感知相关功能定义
 */
class WindowGetter {

public:
    /**
     * @brief 获取鼠标所在窗口的区域
     * @param screen 鼠标所在的屏幕
     * @param host 截图程序所在的窗口(该窗口需要被排除)
     * @return
     */
    static QRect winGeometry(QScreen *screen,QWidget *host);

};

#endif // SCREENSNAP_H
