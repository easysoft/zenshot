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
