#ifndef POINTSHAPE_H
#define POINTSHAPE_H

#include "core/shape.h"

#include <QVector>
#include <QPoint>
#include <QColor>

/**
 * @class : PointsShape
 * @brief : 多点组成的图形基类定义
 * @note  : 提供直线，折线，之类由点构成图形的基本功能
 */
class PointsShape : public Shape
{
public:
    explicit PointsShape(Workspace *m_workspace);

    /**
     * @brief 获取点的总数量
     * @return 返回整数
     */
    int count();

    /**
     * @brief 获取指定位置的点
     * @param index 指定位置的索引
     * @return 返回位置的坐标
     */
    QPoint pointAt(int index);

    /**
     * @brief 设置指定位置点的坐标
     * @param point 点的坐标
     * @param index 指定位置的索引
     */
    void setPointAt(QPoint point, int index);

    /**
     * @brief 移除指定位置的点
     * @param index 指定位置的索引
     */
    void removePointAt(int index);

    /**
     * @brief 在末尾添加一个点
     * @param point 新增加的点
     */
    void addPoint(QPoint point);

    QRect boundary();
    QVector<Handle*> handles();
    bool contain(QPoint point);
    void move(QPoint offsetPoint);
    void draw(QPainter &painter);

protected:
    int m_lineWidth;              //线的线宽
    QColor m_lineColor;           //线的颜色
    Qt::PenStyle m_lineStyle;     //线条样式

    QVector<QPoint> m_points;     //点列表
};

#endif // POINTSHAPE_H
