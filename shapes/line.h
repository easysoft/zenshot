#ifndef LINE_H
#define LINE_H

#include "core/pointshape.h"

class Line : public PointsShape
{
public:
    explicit Line(Workspace *m_workspace);

    QString type();
    bool contain(QPoint point);
    void draw(QPainter &painter);

protected:
    void loadPropsImpl(Store *store);
    void savePropsImpl(Store *store);      
};

#endif // LINE_H
