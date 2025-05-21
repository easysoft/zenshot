/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef MOSAICCREATETOOL_H
#define MOSAICCREATETOOL_H

#include "core/tool.h"
#include "shapes/mosaic.h"

#include <memory>

class MosaicCreateTool : public Tool
{
public:
    explicit MosaicCreateTool(Workspace *m_workspace);

    QString forType();
    virtual void setCursor();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    std::shared_ptr<Mosaic> m_shape;
};

#endif // MOSAICCREATETOOL_H
