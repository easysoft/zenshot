/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef AREAMOVETOOL_H
#define AREAMOVETOOL_H

#include "core/tool.h"

/**
 * @class : AreaMoveTool
 * @brief : 截图区域移动工具类
 * @note  : 截图区域移动工具类
 */
class AreaMoveTool : public Tool
{
public:
    explicit AreaMoveTool(Workspace *m_workspace);

    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);
};

#endif // AREAMOVETOOL_H
