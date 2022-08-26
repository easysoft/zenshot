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

#ifndef TEXTCONTENTCOMMAND_H
#define TEXTCONTENTCOMMAND_H

#include "core/command.h"
#include "shapes/text.h"

/**
 * @class : TextContentCommand
 * @brief : 文本内容命令定义
 * @note  : 回退显示旧的文字，恢复使用新的文字
 */
class TextContentCommand : public Command
{
public:
    explicit TextContentCommand(Workspace *workspace, std::shared_ptr<Text> shape,QString preContent);

    void undo();
    void redo();

private:
    std::shared_ptr<Text> m_shape;

    QString m_oldContent;   //旧的文字内容
    QString m_nowContent;   //新的文字内容  
};

#endif // TEXTCONTENTCOMMAND_H
