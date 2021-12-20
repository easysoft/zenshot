#ifndef CURVEBAR_H
#define CURVEBAR_H

#include "core/propsbar.h"
#include "controls/colorwidget.h"
#include "controls/sizeinputwidget.h"

/**
 * @class : CurveBar
 * @brief : 铅笔属性面板定义
 * @note  : 管理铅笔属性设置
 */
class CurveBar : public PropsBar
{
    Q_OBJECT
public:
    explicit CurveBar(Workspace *m_workspace);

private:
    ColorWidget *m_colorWidget;   //颜色组件对象
    SizeInputWidget *m_sizeWidget;     //尺寸组件对象

protected:
    void createWidget();
    void loadProps();
    void saveProps();
    void connectEvents();
};

#endif // CURVEBAR_H
