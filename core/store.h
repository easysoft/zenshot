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
