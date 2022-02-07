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

#ifndef PROPSCOMMAND_H
#define PROPSCOMMAND_H

#include "core/shape.h"
#include "core/command.h"
#include "core/store.h"
#include "stores/memorystore.h"

/**
 * @class : PropsCommand
 * @brief : 属性命令定义
 * @note  : 回退使用旧的属性，恢复使用新的属性
 */
class PropsCommand : public Command
{
public:
    explicit PropsCommand(Workspace *workspace,Shape *shape,MemoryStore oldStore,MemoryStore nowStore);

    void undo();
    void redo();

private:
    Shape *m_shape;
    MemoryStore m_oldStore;   //旧属性存储位置对象
    MemoryStore m_nowStore;   //新属性存储位置对象
};

#endif // PROPSCOMMAND_H
