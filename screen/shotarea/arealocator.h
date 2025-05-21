/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef AREALOCATOR_H
#define AREALOCATOR_H

#include "core/locator.h"
#include "core/utils.h"

class ShotArea;

class AreaLocator : public Locator
{
public:
    AreaLocator(ShotArea* shape,Utils::RectAnchor anchor);

    Utils::RectAnchor anchor() const;
    void setAnchor(const Utils::RectAnchor &anchor);

    QPoint location();
    void setLocation(QPoint point);

private:
    Utils::RectAnchor m_anchor;
    ShotArea* m_shotArea;
};

#endif // AREALOCATOR_H
