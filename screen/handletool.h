/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef HANDLETOOL_H
#define HANDLETOOL_H

#include "core/tool.h"
#include "core/handle.h"

/**
 * @class : HandleTool
 * @brief : 控制手柄操作工具类定义
 * @note  : 提供控制手柄的移动功能
 */
class HandleTool : public Tool
{
public:
    /**
     * @brief HandleTool
     * @param m_workspace 工作空间
     * @param m_handle 目标控制手柄
     */
    explicit HandleTool(Workspace *m_workspace,Handle *m_handle);

private:
    QPoint m_pressPosition;  //鼠标按下时的坐标
    Handle *m_handle;        //要操作的控制手柄

public:
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);
};

#endif // HANDLETOOL_H
