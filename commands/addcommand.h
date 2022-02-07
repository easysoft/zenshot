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

#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "core/command.h"
#include "core/shape.h"

/**
 * @class : AddCommand
 * @brief : 新增命令定义
 * @note  : 删除新增的图形，恢复删除的图形
 */
class AddCommand : public Command
{
public:
    /**
     * @brief AddCommand
     * @param workspace 工作空间
     * @param shape 目标图形
     */
    explicit AddCommand(Workspace *workspace,Shape *shape);

    void undo();
    void redo();

private:
    Shape *m_shape;    
};

#endif // ADDCOMMAND_H
