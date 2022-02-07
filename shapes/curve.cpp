/* Copyright (C) 2021 Nature Easy Soft Network Technology Co., LTD
 *
 * This file is part of Zenshot (https://github.com/easysoft/zenshot/).
 *
 * Zenshot is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zenshot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zenshot. If not, see <https://www.gnu.org/licenses/>.
 */

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
