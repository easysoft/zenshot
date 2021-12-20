#ifndef MOSAICBAR_H
#define MOSAICBAR_H

#include "core/propsbar.h"
#include "controls/sizeinputwidget.h"

/**
 * @class : MosaicBar
 * @brief : 马赛克属性面板定义
 * @note  : 马赛克铅笔属性设置
 */
class MosaicBar : public PropsBar
{
    Q_OBJECT
public:
    explicit MosaicBar(Workspace *m_workspace);

private:
    SizeInputWidget *m_sizeWidget;  //尺寸组件对象

protected:
    void createWidget();
    void loadProps();
    void saveProps();
    void connectEvents();
};

#endif // MOSAICBAR_H
