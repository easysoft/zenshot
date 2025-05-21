/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef ARROW_H
#define ARROW_H

#include "core/pointshape.h"

#include <QPainterPath>

class Arrow : public PointsShape
{
public:
    explicit Arrow(Workspace *m_workspace);

    QString type();
    void draw(QPainter &painter);
    bool contain(QPoint point);

protected:
    void loadPropsImpl(Store *store);
    void savePropsImpl(Store *store);

private:
    QPainterPath getPath();
};

#endif // ARROW_H
