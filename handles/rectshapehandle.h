#ifndef RECTSHAPEHANDLE_H
#define RECTSHAPEHANDLE_H

#include "core/handle.h"
#include "locators/rectlocator.h"
#include "core/utils.h"

/**
 * @class : RectShapeHandle
 * @brief : 矩形图形的控制手柄类定义
 * @note  : 图形选中后出现，鼠标拖拽控制手柄可以修改图形
 */
class RectShapeHandle : public Handle
{
public:
    explicit RectShapeHandle(RectLocator *m_locator);

    void flipAnchorX();
    void flipAnchorY();
    void setCursor(QWidget *targetUI);

private:
    Utils::RectAnchor m_anchor;

};

#endif // RECTSHAPEHANDLE_H
