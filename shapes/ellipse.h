#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "core/rectshape.h"

class Ellipse : public RectShape
{
public:
    Ellipse(Workspace *m_workspace);

    QString type();
    bool contain(QPoint point);
    void draw(QPainter &painter);

protected:
    void loadPropsImpl(Store *store);
    void savePropsImpl(Store *store);
};

#endif // ELLIPSE_H
