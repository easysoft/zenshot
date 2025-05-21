/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef MOVETOOL_H
#define MOVETOOL_H

#include <QPoint>

#include "core/tool.h"
#include "core/shape.h"

/**
 * @class : MoveTool
 * @brief : 移动工具类定义
 * @note  : 提供移动图形功能
 */
class MoveTool : public Tool
{
public:
    explicit MoveTool(Workspace *m_workspace, std::shared_ptr<Shape> shape);

private:
    std::shared_ptr<Shape> m_shape;

    QPoint m_start;  //鼠标移动的起始点
    QPoint m_end;    //鼠标移动的结束点

public:
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);
};

#endif // MOVETOOL_H
