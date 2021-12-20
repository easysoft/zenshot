#ifndef ARROWBAR_H
#define ARROWBAR_H

#include "core/propsbar.h"
#include "controls/colorwidget.h"
#include "controls/sizeinputwidget.h"

/**
 * @class : ArrowBar
 * @brief : 箭头属性面板定义
 * @note  : 管理箭头属性设置
 */
class ArrowBar : public PropsBar
{
    Q_OBJECT
public:
    explicit ArrowBar(Workspace *m_workspace);

private:
    ColorWidget *m_colorWidget;  //颜色组件对象
    SizeInputWidget *m_sizeWidget;    //尺寸属性对象

protected:
    void createWidget();
    void loadProps();
    void saveProps();
    void connectEvents();
};

#endif // ARROWBAR_H
