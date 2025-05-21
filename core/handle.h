/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef HANDLE_H
#define HANDLE_H

#include <QPainter>
#include <QWidget>

#include "core/locator.h"

/**
 * @class : Handle
 * @brief : 控制手柄基类定义
 * @note  : 用于修改图形数据，实现图形编辑功能
 */
class Handle
{
public:
    /**
     * @brief Handle
     * @param locator 关联的定位器
     */
    explicit Handle(Locator *m_locator);

    /**
     * @brief 获取对应的定位器
     * @return
     */
    Locator *locator() const;

    /**
     * @brief 获取对应的边界区域
     * @return
     */
    virtual QRect boundary();

    /**
     * @brief 判断是否包含给定的点
     * @param point 给定的点
     * @return
     */
    bool contain(QPointF point);

    /**
     * @brief 控制手柄移动
     * @param point 移动的相对位置
     */
    void move(QPoint point);

    /**
     * @brief 绘制控制手柄(默认绘制圆形)
     * @param painter 绘图平面
     */
    virtual void draw(QPainter &painter);

    /**
     * @brief 设置鼠标形状
     * @param targetUI 关联的UI
     */
    virtual void setCursor(QWidget *targetUI);

protected:
    Locator *m_locator;


};

#endif // HANDLE_H
