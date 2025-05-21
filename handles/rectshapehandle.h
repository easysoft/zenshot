/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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
