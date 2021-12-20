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
