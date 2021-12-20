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
