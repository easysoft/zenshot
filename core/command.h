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

#ifndef COMMAND_H
#define COMMAND_H

class Workspace;

/**
 * @class : Command
 * @brief : 命令基类定义
 * @note  : 取消操作，恢复取消的操作
 */
class Command
{
public:

    explicit Command(Workspace *workspace);

    /**
     * @brief 取消操作
     */
    virtual void undo()=0;

    /**
     * @brief 恢复操作
     */
    virtual void redo()=0;

protected:
    Workspace *m_workspace;
};

#endif // COMMAND_H
