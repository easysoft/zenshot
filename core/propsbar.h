#ifndef PROPSBAR_H
#define PROPSBAR_H

#include <QWidget>
#include <QHBoxLayout>

#include "stores/localstore.h"

class Workspace;

/**
 * @class : PropsBar
 * @brief : 属性面板基类定义
 * @note  : 提供图形图形设置
 */
class PropsBar : public QWidget
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
