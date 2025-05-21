/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef AREAHANDLETOOL_H
#define AREAHANDLETOOL_H

#include "core/tool.h"
#include "core/handle.h"

/**
 * @class : AreaHandleTool
 * @brief : 截图区域控制手柄操作工具类
 * @note  : 截图区域控制手柄操作工具类
 */
class AreaHandleTool : public Tool
{
public:
    explicit AreaHandleTool(Workspace *m_workspace,Handle *m_handle);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    Handle *m_handle;

};

#endif // AREAHANDLETOOL_H
