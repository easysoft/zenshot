#ifndef ELLIPSEBAR_H
#define ELLIPSEBAR_H

#include "core/propsbar.h"
#include "controls/colorwidget.h"
#include "controls/sizeinputwidget.h"
#include "controls/pencombobox.h"

/**
 * @class : EllipseBar
 * @brief : 椭圆属性面板定义
 * @note  : 椭圆铅笔属性设置
 */
class EllipseBar : public PropsBar
{
    Q_OBJECT
public:
    explicit EllipseBar(Workspace *m_workspace);

private:
    ColorWidget *m_colorWidget;            //颜色组件对象
    SizeInputWidget *m_sizeWidget;              //尺寸组件对象
    PenCombobox *m_penStyleCombobox;  //线条组件对象

protected:
    void createWidget();
    void loadProps();
    void saveProps();
    void connectEvents();
};

#endif // ELLIPSEBAR_H
