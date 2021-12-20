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
