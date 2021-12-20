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
