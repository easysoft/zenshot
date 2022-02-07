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

#ifndef OPERLOGGER_H
#define OPERLOGGER_H

#include <QVector>
#include <QObject>
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
    static void add(Command* command);

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

private:
    UserOper(){};
    static UserOper* m_instance;

    QVector<Command*> m_undoList;
    QVector<Command*> m_redoList;

    void addImpl(Command* command);
    void undoImpl();
    void redoImpl();

    int undoNumImpl();
    int redoNumImpl();

    void addImpl(QVector<Command*> &targetList, Command* item);

signals:
    void changed();
};

#endif // OPERLOGGER_H
