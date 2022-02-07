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

#ifndef PROPSBAR_H
#define PROPSBAR_H

#include <QWidget>
#include <QHBoxLayout>

#include "stores/localstore.h"
#include "core/gscale.h"

class Workspace;

/**
 * @class : PropsBar
 * @brief : 属性面板基类定义
 * @note  : 提供图形图形设置
 */
class PropsBar : public QWidget, public GScale
{
    Q_OBJECT
public:
    explicit PropsBar(Workspace *m_workspace);

protected:
    LocalStore *m_store;     //本地存储对象
    Workspace *m_workspace;  //工作空间
    QHBoxLayout *m_layout;   //根布局管理器

    /**
     * @brief 添加垂直分割条
     */
    void addSeperator();

    /**
     * @brief 创建界面
     */
    virtual void createWidget()=0;

    /**
     * @brief 加载属性
     */
    virtual void loadProps()=0;

    /**
     * @brief 保存属性
     */
    virtual void saveProps()=0;

    /**
     * @brief 链接信号，槽
     */
    virtual void connectEvents()=0;

protected slots:
    void propsChanged();
};

#endif // PROPSBAR_H
