/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "pointlocator.h"

PointLocator::PointLocator(PointsShape *shape,int index):Locator()
{
    this->m_shape = shape;
    this->m_index = index;
}

void PointLocator::setLocation(QPoint point)
{
    m_shape->setPointAt(point,m_index);
}

QPoint PointLocator::location()
{
    return m_shape->pointAt(m_index);
}
