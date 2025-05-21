/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef LOCATOR_H
#define LOCATOR_H

#include <QPoint>
#include <QRect>

/**
 * @class : Locator
 * @brief : 定位器基类定义
 * @note  : 用于定位图形中的关键点
 */
class Locator
{
public:
    explicit Locator();

    /**
     * @brief 获取对应的坐标点
     * @return 坐标值
     */
    virtual QPoint location() = 0;

    /**
     * @brief 设置对应点的坐标
     * @param point
     */
    virtual void setLocation(QPoint point) = 0;
};

#endif // LOCATOR_H
