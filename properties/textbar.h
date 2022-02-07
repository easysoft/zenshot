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

#ifndef TEXTBAR_H
#define TEXTBAR_H

#include "core/propsbar.h"
#include "controls/sizewidget.h"
#include "controls/colorwidget.h"

#include <QComboBox>
#include <QFontComboBox>
#include <QCheckBox>

/**
 * @class : TextBar
 * @brief : 文本属性面板定义
 * @note  : 文本铅笔属性设置
 */
class TextBar : public PropsBar
{
    Q_OBJECT
public:
    explicit TextBar(Workspace *m_workspace);

private:
    QComboBox *m_fontComboxBox;        //字体组件对象
    QComboBox *m_sizeComboBox;         //字号组件对象
    ColorWidget *m_colorWidget;        //颜色组件对象
    QCheckBox *m_boldCheckBox;         //粗体组件对象
    QCheckBox *m_italicCheckBox;       //斜体组件对象
    QCheckBox *m_underlineCheckBox;    //下划线组件对象


protected:
    void createWidget();
    void loadProps();
    void saveProps();
    void connectEvents();

private slots:
    void indexChanged(int index);

};

#endif // TEXTBAR_H
