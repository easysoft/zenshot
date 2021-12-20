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
