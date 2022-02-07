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

#ifndef STORE_H
#define STORE_H

#include <QVariant>
#include <QColor>

/**
 * @class : Store
 * @brief : 存储基类定义
 * @note  : 提供属性值的读，写
 */
class Store
{
public:
    Store();

    /**
     * @brief 值写到指定的位置
     * @param group 分组
     * @param key 关键字
     * @param value 值
     */
    virtual void write(const QString &group,const QString &key,const QVariant &value) = 0;

    /**
     * @brief 从指定的位置读取值
     * @param group 分组
     * @param key 关键字
     * @param defaultvalue 默认值
     * @return 读到的值
     */
    virtual QVariant read(const QString &group,const QString &key,const QVariant &defaultvalue) = 0;

    /**
     * @brief 颜色值写到指定的位置
     * @param group 分组
     * @param key 关键字
     * @param value 颜色
     */
    void writeColor(const QString &group,const QString &key,const QColor &value);

    /**
     * @brief 从指定的位置读取颜色值
     * @param group 分组
     * @param key 关键字
     * @param defaultvalue 默认值
     * @return
     */
    QColor readColor(const QString &group,const QString &key,const QColor &defaultvalue);

    /**
     * @brief 笔触样式写到指定的位置
     * @param group 分组
     * @param key 关键字
     * @param value 值
     */
    void writePenStyle(const QString &group,const QString &key,const Qt::PenStyle &value);

    /**
     * @brief 从指定的位置读取笔触样式
     * @param group 分组
     * @param key 关键字
     * @param defaultvalue 默认笔触样式
     * @return 值
     */
    Qt::PenStyle readPenStyle(const QString &group,const QString &key,const Qt::PenStyle &defaultvalue);
};

#endif // STORE_H
