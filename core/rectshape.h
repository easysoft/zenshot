/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef RECTSHAPE_H
#define RECTSHAPE_H

#include <QRect>
#include "core/shape.h"

/**
 * @class : RectShape
 * @brief : 由矩形构成的图形基类
 * @note  : 提供矩形，椭圆图形的基本功能
 */
class RectShape : public Shape
{
public:
    explicit RectShape(Workspace *m_workspace);

    /**
     * @brief 设置矩形
     * @param rect 目标矩形
     */
    void setBoundary(QRect rect);

    /**
     * @brief 获取矩形线宽
     * @return
     */
    int lineWidth() const;

    QRect boundary();
    QVector<Handle*> handles();
    bool contain(QPoint point);
    void move(QPoint offsetPoint);
    void draw(QPainter &painter);

protected:
    QRect m_boundary;            //矩形区域

    int m_lineWidth;             //线的宽度
    QColor m_lineColor;          //线的颜色
    Qt::PenStyle m_lineStyle;    //线条样式
};

#endif // RECTSHAPE_H
