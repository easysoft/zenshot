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

#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "core/command.h"
#include "core/shape.h"

/**
 * @class : DeleteCommand
 * @brief : 删除命令类定义
 * @note  : 添加删除的图形，删除恢复的图形
 */
class DeleteCommand : public Command
{
public:
    explicit DeleteCommand(Workspace *workspace, std::shared_ptr<Shape> shape);

    void undo();
    void redo();

private:
    std::shared_ptr<Shape> m_shape;
};

#endif // DELETECOMMAND_H
