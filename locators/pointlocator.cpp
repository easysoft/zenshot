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
