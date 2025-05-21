/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef MOSAIC_H
#define MOSAIC_H

#include "core/pointshape.h"

class Mosaic : public PointsShape
{
public:
    explicit Mosaic(Workspace *m_workspace);

    QString type();
    QRect boundary();
    QVector<Handle *> handles();
    void draw(QPainter &painter);
    bool contain(QPoint point);

protected:
    void loadPropsImpl(Store *store);
    void savePropsImpl(Store *store);

private:
    QVector<QRect> getRects();    
};

#endif // MOSAIC_H
