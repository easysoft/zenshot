/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef LINECREATETOOL_H
#define LINECREATETOOL_H

#include "core/tool.h"
#include "shapes/line.h"

class LineCreateTool : public Tool
{
public:
    explicit LineCreateTool(Workspace *m_workspace);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    std::shared_ptr<Line> m_shape;
    bool m_isInlist;

};

#endif // LINECREATETOOL_H
