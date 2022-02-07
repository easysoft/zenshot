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

#ifndef LOCATORCOMMAND_H
#define LOCATORCOMMAND_H

#include "core/command.h"
#include "core/locator.h"

#include <QPoint>

/**
 * @class : LocatorCommand
 * @brief : 定位器命令定义
 * @note  : 回退到旧的位置，重新恢复到新的位置
 */
class LocatorCommand : public Command
{
public:
    explicit LocatorCommand(Workspace *workspace,Locator *locator,QPoint oldPosition, QPoint newPosition);

    void undo();
    void redo();

private:
    QPoint m_oldPosition;    //旧的位置
    QPoint m_newPosition;    //新的位置

    Locator *m_locator; 
};

#endif // LOCATORCOMMAND_H
