/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef OPERLOGGER_H
#define OPERLOGGER_H

#include <QVector>
#include <QObject>
#include <memory>
#include "core/command.h"

/**
 * @class : Operater
 * @brief : 用户操作单例类定义
 * @note  : 记录用户操作，提供撤销返回操作
 */
class UserOper : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 获取操作单例对象
     * @return 返回操作对象
     */
    static UserOper* instance();

    /**
     * @brief 添加当前执行的操作命令
     * @param command 操作命令
     */
    static void add(std::shared_ptr<Command> command);

    /**
     * @brief 取消操作
     */
    static void undo();

    /**
     * @brief 恢复之前取消的操作
     */
    static void redo();

    /**
     * @brief 获取待取消的数量
     * @return
     */
    static int undoNum();

    /**
     * @brief 获取待重做的数量
     * @return
     */
    static int redoNum();

    /**
     * @brief 本次截图结束，清除缓冲区
     * @return
     */
    static void cleanAll();

private:
    UserOper(){};
    static UserOper* m_instance;

    QVector<std::shared_ptr<Command>> m_undoList;
    QVector<std::shared_ptr<Command>> m_redoList;

    void addImpl(std::shared_ptr<Command> command);
    void undoImpl();
    void redoImpl();

    int undoNumImpl();
    int redoNumImpl();

    void addImpl(QVector<std::shared_ptr<Command>> &targetList, std::shared_ptr<Command> item);
    void clean();

signals:
    void changed();
};

#endif // OPERLOGGER_H
