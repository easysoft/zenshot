/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef CURVECREATETOOL_H
#define CURVECREATETOOL_H

#include "core/tool.h"
#include "shapes/curve.h"

class CurveCreateTool : public Tool
{
public:
    explicit CurveCreateTool(Workspace *m_workspace);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    std::shared_ptr<Curve> m_shape;

};

#endif // CURVECREATETOOL_H
