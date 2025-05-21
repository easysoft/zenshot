/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef RECTLOCATOR_H
#define RECTLOCATOR_H

#include <QPoint>

#include "core/locator.h"
#include "core/rectshape.h"
#include "core/utils.h"

/**
 * @class : RectLocator
 * @brief : 基于矩形区域的定位
 * @note  : 矩形四个角和四条边的中间共8个点坐标的定位
 */
class RectLocator : public Locator
{
public:
    explicit RectLocator(RectShape* shape,Utils::RectAnchor anchor);

    Utils::RectAnchor anchor();
    void setAnchor(Utils::RectAnchor value);

    QPoint location();
    void setLocation(QPoint point);

private:
    Utils::RectAnchor m_anchor;
    RectShape* m_shape;
};

#endif // RECTLOCATOR_H
