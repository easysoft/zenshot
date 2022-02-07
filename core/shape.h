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

#ifndef SHAPE_H
#define SHAPE_H

#include <QVector>
#include <QRect>
#include <QPainter>
#include <QMap>
#include <QVariant>

#include "core/handle.h"
#include "core/utils.h"
#include "core/store.h"

class Workspace;

/**
 * @class : Shape
 * @brief : 图形基类定义
 * @note  : 提供图形基本功能
 */
class Shape
{
public:
    explicit Shape(Workspace *m_workspace);

    /**
     * @brief 获取图形类型
     * @return 字符串
     */
    virtual QString type();

    /**
     * @brief 获取工作空间
     * @return
     */
    Workspace* workspace();

    /**
     * @brief 获取选中标识
     * @return 选中：true 未选中：false
     */
    bool selected();

    /**
     * @brief 设置选中标识
     * @param flag 选中：true 未选中：false
     */
    void setSelected(bool flag);

    /**
     * @brief 获取边界矩形
     * @return 返回矩形对象
     */
    virtual QRect boundary()=0;

    /**
     * @brief 获取控制手柄
     * @return 控制手柄集合
     */
    virtual QVector<Handle*> handles()=0;

    /**
     * @brief 判断是否包含给点的带你
     * @param point 给定的点
     * @return
     */
    virtual bool contain(QPoint point) = 0;

    /**
     * @brief 移动图形
     * @param offset
     */
    virtual void move(QPoint offsetPoint) = 0;

    /**
     * @brief 绘制图形
     * @param painter 绘图平面
     */
    virtual void draw(QPainter &painter)=0;

    /**
     * @brief 加载属性
     * @param store 属性存储位置(nullptr：表示本地存储)
     */
    void loadProps(Store *store = nullptr);

    /**
     * @brief 保存属性
     * @param store store 属性存储位置(nullptr：表示本地存储)
     */
    void saveProps(Store *store = nullptr);

protected:
    bool m_selected;           //是否选中
    Workspace* m_workspace;    //工作空间

    /**
     * @brief 从指定存储加载属性
     * @param store 指定位置
     */
    virtual void loadPropsImpl(Store *store)=0;

    /**
     * @brief 保存属性到指定位置
     * @param store 指定位置
     */
    virtual void savePropsImpl(Store *store)=0;

    /**
     * @brief 绘制蚂蚁指示器(用于图形选中后的轮廓指示)
     * @param painter 绘图平面
     * @param rect 绘制的矩形区域
     * @param extend 矩形区域扩展
     */
    void drawAntIndicator(QPainter &painter,QRect rect,float extend=0);
};

#endif // SHAPE_H
