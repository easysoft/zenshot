#include "arealocator.h"
#include "screen/shotarea.h"
#include "screen/shotarea/areahandle.h"
#include "screen/workspace.h"

#include <QtMath>

AreaLocator::AreaLocator(ShotArea* shape,Utils::RectAnchor anchor)
{
    this->m_shotArea = shape;
    this->m_anchor = anchor;
}

Utils::RectAnchor AreaLocator::anchor() const
{
    return m_anchor;
}

void AreaLocator::setAnchor(const Utils::RectAnchor &anchor)
{
    m_anchor = anchor;
}

QPoint AreaLocator::location()
{
    QRect boundary = m_shotArea->boundary();

    int x = boundary.x() + boundary.width()/2;
    int y = boundary.y() + boundary.height()/2;

    switch(m_anchor) {
    case Utils::RECT_TOP_LEFT:
        x = boundary.x();
        y = boundary.y();
        break;
    case Utils::RECT_TOP_MIDDLE:
        x = boundary.x() + boundary.width()/2;
        y = boundary.y();
        break;
    case Utils::RECT_TOP_RIGHT:
        x = boundary.x() + boundary.width();
        y = boundary.y();
        break;
    case Utils::RECT_LEFT_MIDDLE:
        x = boundary.x();
        y = boundary.y() + boundary.height()/2;
        break;
    case Utils::RECT_RIGHT_MIDDLE:
        x = boundary.x() + boundary.width();
        y = boundary.y() + boundary.height()/2;
        break;
    case Utils::RECT_BOTTOM_LEFT:
        x = boundary.x();
        y = boundary.y() + boundary.height();
        break;
    case Utils::RECT_BOTTOM_MIDDLE:
        x = boundary.x() + boundary.width()/2;
        y = boundary.y() + boundary.height();
        break;
    case Utils::RECT_BOTTOM_RIGHT:
        x = boundary.x() + boundary.width();
        y = boundary.y() + boundary.height();
        break;
    }

    return  QPoint(x,y);
}

void AreaLocator::setLocation(QPoint point)
{
    QRectF boundary = m_shotArea->boundary();

    int x1 = boundary.x();
    int y1 = boundary.y();
    int x2 = boundary.x() + boundary.width();
    int y2 = boundary.y() + boundary.height();

    switch (m_anchor) {
        case Utils::RECT_TOP_LEFT:
        x1 = point.x();
        y1 = point.y();
        break;
    case Utils::RECT_TOP_MIDDLE:
        y1 = point.y();
        break;
    case Utils::RECT_TOP_RIGHT:
        y1 = point.y();
        x2 = point.x();
        break;
    case Utils::RECT_LEFT_MIDDLE:
        x1 = point.x();
        break;
    case Utils::RECT_RIGHT_MIDDLE:
        x2 = point.x();
        break;
    case Utils::RECT_BOTTOM_LEFT:
        x1 = point.x();
        y2 = point.y();
        break;
    case Utils::RECT_BOTTOM_MIDDLE:
        y2 = point.y();
        break;
    case Utils::RECT_BOTTOM_RIGHT:
        x2 = point.x();
        y2 = point.y();
        break;
    }

    bool isXFlip = false;
    bool isYFlip = false;

    if(x1 > x2) isXFlip = true;
    if(y1 > y2) isYFlip = true;

    if(isXFlip == false && isYFlip == false)
    {
        float x = qMin(x1,x2);
        float y = qMin(y1,y2);
        float w = qAbs(x2 - x1);
        float h = qAbs(y2 - y1);

        QRect newBoundary(x,y,w,h);
        this->m_shotArea->setBoundary(newBoundary);
    }
    else if(m_shotArea->workspace()->shapeCount() == 0)
    {
        float x = qMin(x1,x2);
        float y = qMin(y1,y2);
        float w = qAbs(x2 - x1);
        float h = qAbs(y2 - y1);

        QRect newBoundary(x,y,w,h);
        this->m_shotArea->setBoundary(newBoundary);

        QVector<Handle*> handles = m_shotArea->handles();
        for(Handle *hdl:handles)
        {
            AreaHandle *areaHdl = dynamic_cast<AreaHandle*>(hdl);

            if(isXFlip) areaHdl->flipAnchorX();
            if(isYFlip) areaHdl->flipAnchorY();
        }
    }
    else
    {
        if(x1 > x2)
        {
            x1 = boundary.x();
            x2 = boundary.x() + boundary.width();
        }

        if(y1 > y2)
        {
            y1 = boundary.y();
            y2 = boundary.y() + boundary.height();
        }

        float x = qMin(x1,x2);
        float y = qMin(y1,y2);
        float w = qAbs(x2 - x1);
        float h = qAbs(y2 - y1);

        QRect newBoundary(x,y,w,h);
        this->m_shotArea->setBoundary(newBoundary);
    }
}
