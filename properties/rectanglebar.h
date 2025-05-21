/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef RECTANGLEBAR_H
#define RECTANGLEBAR_H

#include "core/propsbar.h"
#include "controls/colorwidget.h"
#include "controls/sizeinputwidget.h"
#include "controls/pencombobox.h"

/**
 * @class : RectangleBar
 * @brief : 矩形属性面板定义
 * @note  : 矩形克铅笔属性设置
 */
class RectangleBar : public PropsBar
{
    Q_OBJECT
public:
    explicit RectangleBar(Workspace *m_workspace);

private:
    ColorWidget *m_colorWidget;           //颜色组件对象
    SizeInputWidget *m_sizeWidget;             //尺寸组件对象
    PenCombobox *m_penStyleCombobox; //线条组件对象

protected:
    void createWidget();
    void loadProps();
    void saveProps();
    void connectEvents();
};

#endif // RECTANGLEBAR_H
