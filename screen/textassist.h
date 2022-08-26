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

#ifndef TEXTASSIST_H
#define TEXTASSIST_H

#include <QPoint>

#include "controls/textwidget.h"
#include "shapes/text.h"

class Workspace;

/**
 * @class : TextAssist
 * @brief : 文本编辑辅助类定义
 * @note  : 提供文本的在位输入，修改功能
 */
class TextAssist
{
public:
    explicit TextAssist(Workspace *m_workspace);

    /**
     * @brief 获取是否正在编辑
     * @return
     */
    bool editing() const;

    /**
     * @brief 关联文本图形对象并启动编辑
     * @param m_shape
     */
    void attach(std::shared_ptr<Text> m_shape);

    /**
     * @brief 接触关联，并结束文本编辑
     */
    void unAttach();

    /**
     * @brief 更新属性
     */
    void refreshProps();

    void cleanup();

private:
    bool m_editing;           //是否正在编辑标识
    std::shared_ptr<Text> m_shape;            //关联的文本对象
    QString m_preContent;     //文本图形之前的内容

    TextWidget *m_textWidget; //文本编辑组件对象
    Workspace *m_workspace;   //工作空间
};

#endif // TEXTASSIST_H
