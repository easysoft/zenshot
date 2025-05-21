/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef WORKAREACREATETOOL_H
#define WORKAREACREATETOOL_H

#include "core/tool.h"
#include <QRect>
#include <QPoint>

/**
 * @class : AreaCreateTool
 * @brief : 截图区域创建工具
 * @note  : 截图区域创建工具
 */
class AreaCreateTool : public Tool
{
public:
    explicit AreaCreateTool(Workspace *m_workspace);

    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint,QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);


private:
    bool m_isMousePress;
    QPoint m_startPoint;
};

#endif // WORKAREACREATETOOL_H
