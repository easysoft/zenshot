#include "line.h"
#include "screen/workspace.h"

#include <QtMath>
#include <QRegion>

Line::Line(Workspace *workspace):PointsShape(workspace)
{
    loadProps();
}

QString Line::type()
{
    return Utils::forLineKey();
}

bool Line::contain(QPoint point)
{
    QPointF start = pointAt(0);
    QPointF end = pointAt(1);

    if(m_lineWidth >4)
    {
        double qatan2 = qAtan2(end.y()-start.y(),end.x()-start.x());
        double angle = qatan2*180/M_PI;

        double p1x = start.x() + (m_lineWidth/2)*qCos(angle/180.0*M_PI);
        double p1y = start.y() + (m_lineWidth/2)*qSin(angle/180.0*M_PI);

        double p2x = end.x() + (m_lineWidth/2)*qCos((angle+180)/180.0*M_PI);
        double p2y = end.y() + (m_lineWidth/2)*qSin((angle+180)/180.0*M_PI);

        start = QPointF(p1x,p1y);
        end = QPointF(p2x,p2y);
    }

    if(Utils::distance(start,end,point) <= m_lineWidth/2+Utils::Hit_Snap)
    {
        return true;
    }

    return false;
}

void Line::draw(QPainter &painter)
{
    painter.save();

    QPen pen;
    pen.setWidth(m_lineWidth);
    pen.setColor(m_lineColor);
    pen.setStyle(m_lineStyle);

    painter.setPen(pen);

    QPointF start = pointAt(0);
    QPointF end = pointAt(1);

    if(m_lineWidth >4)
    {
        double qatan2 = qAtan2(end.y()-start.y(),end.x()-start.x());
        double angle = qatan2*180.0/M_PI;

        double p1x = start.x() + (m_lineWidth/2)*qCos(angle/180.0*M_PI);
        double p1y = start.y() + (m_lineWidth/2)*qSin(angle/180.0*M_PI);

        double p2x = end.x() + (m_lineWidth/2)*qCos((angle+180)/180.0*M_PI);
        double p2y = end.y() + (m_lineWidth/2)*qSin((angle+180)/180.0*M_PI);

        if(Utils::distance(start,end) < m_lineWidth*2)
        {
            double x1 = start.x() + (m_lineWidth/2)*qCos((angle+90)/180.0*M_PI);
            double y1 = start.y() + (m_lineWidth/2)*qSin((angle+90)/180.0*M_PI);

            double x2 = start.x() + (m_lineWidth/2)*qCos((angle-90)/180.0*M_PI);
            double y2 = start.y() + (m_lineWidth/2)*qSin((angle-90)/180.0*M_PI);

            double x3 = end.x() + (m_lineWidth/2)*qCos((angle-90)/180.0*M_PI);
            double y3 = end.y() + (m_lineWidth/2)*qSin((angle-90)/180.0*M_PI);

            double x4 = end.x() + (m_lineWidth/2)*qCos((angle+90)/180.0*M_PI);
            double y4 = end.y() + (m_lineWidth/2)*qSin((angle+90)/180.0*M_PI);

            QPolygonF selfPolygon;
            selfPolygon.append(QPointF(x1,y1));
            selfPolygon.append(QPointF(x2,y2));
            selfPolygon.append(QPointF(x3,y3));
            selfPolygon.append(QPointF(x4,y4));

            QPainterPath selClipfPath;
            selClipfPath.addPolygon(selfPolygon);

            QPainterPath globalClipPath;
            globalClipPath.addRect(m_workspace->areaBoundary());

            QPainterPath clipPath = globalClipPath.intersected(selClipfPath);

            painter.setClipPath(clipPath);
        }

        start = QPointF(p1x,p1y);
        end = QPointF(p2x,p2y);
    }

    painter.drawLine(start,end);

    painter.restore();
}

void Line::loadPropsImpl(Store *store)
{
    m_lineWidth = store->read(Utils::forLineKey(),Utils::LineWidthName(),Utils::LineWidthDefault()).toInt();
    m_lineColor = store->readColor(Utils::forLineKey(),Utils::LineColorName(),Utils::LineColorDefault());
    m_lineStyle = store->readPenStyle(Utils::forLineKey(),Utils::LineStyleName(),Utils::LineStyleDefault());
}

void Line::savePropsImpl(Store *store)
{
    store->write(Utils::forLineKey(),Utils::LineWidthName(),m_lineWidth);
    store->writeColor(Utils::forLineKey(),Utils::LineColorName(),m_lineColor);
    store->writePenStyle(Utils::forLineKey(),Utils::LineStyleName(),m_lineStyle);
}

