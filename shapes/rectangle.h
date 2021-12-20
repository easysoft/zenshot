#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "core/rectshape.h"

class Rectangle : public RectShape
{
public:
    explicit Rectangle(Workspace *m_workspace);

    QString type();
    bool contain(QPoint point);
    void draw(QPainter &painter);

protected:
    void loadPropsImpl(Store *store);
    void savePropsImpl(Store *store);

};

#endif // RECTANGLE_H
