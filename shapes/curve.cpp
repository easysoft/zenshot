#include "curve.h"

Curve::Curve(Workspace *workspace):PointsShape(workspace)
{
    m_lineStyle = Qt::SolidLine;

    loadProps();
}

QVector<Handle *> Curve::handles()
{
    QVector<Handle*> results;

    return  results;
}

QString Curve::type()
{
    return Utils::forCurveKey();
}

void Curve::draw(QPainter &painter)
{
    painter.save();

    QPen pen;
    pen.setWidth(m_lineWidth);
    pen.setColor(m_lineColor);
    pen.setStyle(m_lineStyle);

    painter.setPen(pen);

    QPolygon polygon(m_points);
    painter.drawPolyline(polygon);

    painter.restore();

    if(m_selected == true)
    {
        //drawAntIndicator(painter,boundary());
    }
}

void Curve::loadPropsImpl(Store *store)
{
    m_lineWidth = store->read(Utils::forCurveKey(),Utils::CurveWidthName(),Utils::CurveWidthDefault()).toInt();
    m_lineColor = store->readColor(Utils::forCurveKey(),Utils::CurveColorName(),Utils::CurveColorDefault());
}

void Curve::savePropsImpl(Store *store)
{
    store->write(Utils::forCurveKey(),Utils::CurveWidthName(),m_lineWidth);
    store->writeColor(Utils::forCurveKey(),Utils::CurveColorName(),m_lineColor);
}
