/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef RECTCREATETOOL_H
#define RECTCREATETOOL_H

#include "core/tool.h"
#include "shapes/rectangle.h"

class RectCreateTool : public Tool
{
public:
    RectCreateTool(Workspace *m_workspace);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    std::shared_ptr<Rectangle> m_shape;
    QPoint m_startPoint;
    QPoint m_endPoint;
    bool m_isInlist;

};

#endif // RECTCREATETOOL_H
