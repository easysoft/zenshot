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

#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "core/command.h"
#include "core/shape.h"

#include <QPoint>

/**
 * @class : MoveCommand
 * @brief : 移动命令定义
 * @note  : 回退到旧的位置，重新恢复到新的位置
 */
class MoveCommand : public Command
{
public:
    explicit MoveCommand(Workspace *workspace,Shape *shape,QPoint offsetPoint);

    void undo();
    void redo();

private:
    Shape *m_shape;
    QPoint m_offsetPoint;  //移动的偏移量 
};

#endif // MOVECOMMAND_H
