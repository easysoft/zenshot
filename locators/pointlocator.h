/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef POINTLOCATOR_H
#define POINTLOCATOR_H

#include "core/locator.h"
#include "core/pointshape.h"

/**
 * @class : PointLocator
 * @brief : 基于索引的点定位器
 * @note  : 提供基于PointsShape的图形定位功能
 */
class PointLocator : public Locator
{
public:
    explicit PointLocator(PointsShape *shape,int index);

    void setLocation(QPoint point);
    QPoint location();

private:
    int m_index;
    PointsShape *m_shape;
};

#endif // POINTLOCATOR_H
