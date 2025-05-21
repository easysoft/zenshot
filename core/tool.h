/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef TOOL_H
#define TOOL_H

#include <QMouseEvent>
#include <QPoint>

#include "core/utils.h"

#include <memory>

class Workspace;

/**
 * @class : Tool
 * @brief : 鼠标功能基类定义
 * @note  : 涉及到鼠标互操作相关功能定义
 */
class Tool
{
public:
    /**
     * @brief Tool
     * @param workspace 工作空间
     */
    explicit Tool(Workspace *m_workspace);

    virtual ~Tool();

    /**
     * @brief 获取对应的图形类型(针对 create 类的 tool)
     * @return
     */
    virtual QString forType();

    /**
     * @brief 鼠标按下事件回调处理
     * @param mousePoint 鼠标当前位置
     */
    virtual void onMousePress(QPoint mousePoint)=0;

    /**
     * @brief 鼠标移动事件回调处理
     * @param mousePoint 鼠标当前位置
     * @param mouseOffset 鼠标移动偏移量
     */
    virtual void onMouseMove(QPoint mousePoint,QPoint mouseOffset)=0;

    /**
     * @brief 鼠标弹起事件回调处理
     * @param mousePoint 鼠标当前位置
     */
    virtual void onMouseRelease(QPoint mousePoint)=0;

    /**
     * @brief 设置鼠标形状
     */
    virtual void setCursor();

    virtual void cleanup();
protected:
    bool m_autoSelected;
    Workspace *m_workspace;
};

#endif // TOOL_H
