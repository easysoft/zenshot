/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef CURVE_H
#define CURVE_H

#include "core/pointshape.h"

class Curve : public PointsShape
{
public:
    explicit Curve(Workspace *m_workspace);

    QString type();
    QVector<Handle *> handles();
    void draw(QPainter &painter);

protected:
    void loadPropsImpl(Store *store);
    void savePropsImpl(Store *store);
};

#endif // CURVE_H
