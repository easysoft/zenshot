#include "rectlocator.h"
#include "core/utils.h"
#include "screen/workspace.h"
#include "handles/rectshapehandle.h"

#include <QtMath>

RectLocator::RectLocator(RectShape* shape,Utils::RectAnchor anchor)
{
    this->m_shape = shape;
    this->m_anchor = anchor;
}

Utils::RectAnchor RectLocator::anchor()
{
    return m_anchor;
}

void RectLocator::setAnchor(Utils::RectAnchor value)
{
    m_anchor = value;
}

QPoint RectLocator::location()
{
    QRect iBoundary = m_shape->boundary();
    QRect boundary(iBoundary.x() - Utils::Handle_AntLine_Thicknes,
             iBoundary.y() - Utils::Handle_AntLine_Thicknes,
             iBoundary.width() + Utils::Handle_AntLine_Thicknes*2,
             iBoundary.height() + Utils::Handle_AntLine_Thicknes*2);

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

void RectLocator::setLocation(QPoint point)
{
    QRectF boundary = m_shape->boundary();

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

    float x = x1 < x2 ? x1 : x2;
    float y = y1 < y2 ? y1 : y2;
    float w = qAbs(x2 - x1);
    float h = qAbs(y2 - y1);

    if(w <2 ) w = 2;
    if(h <2 ) h = 2;

    QRect newBoundary(x,y,w,h);
    this->m_shape->setBoundary(newBoundary);

    bool isXFlip = false;
    bool isYFlip = false;

    if(x1 > x2) isXFlip = true;
    if(y1 > y2) isYFlip = true;

    if(isXFlip == true || isYFlip == true)
    {
        Workspace *workspace = m_shape->workspace();
        QVector<Handle*> handles = workspace->activeHandles();

        for(Handle *hdl:handles)
        {
            RectShapeHandle *rectHdl = dynamic_cast<RectShapeHandle*>(hdl);

            if(isXFlip) rectHdl->flipAnchorX();
            if(isYFlip) rectHdl->flipAnchorY();
        }
    }
}

//void RectLocator::setLocation(QPoint point)
//{
//    QRectF boundary = m_shape->boundary();

//    float x1 = boundary.x();
//    float y1 = boundary.y();
//    float x2 = boundary.x() + boundary.width();
//    float y2 = boundary.y() + boundary.height();

//    switch (m_anchor) {
//        case Utils::RECT_TOP_LEFT:
//        x1 = point.x();
//        y1 = point.y();
//        break;
//    case Utils::RECT_TOP_MIDDLE:
//        y1 = point.y();
//        break;
//    case Utils::RECT_TOP_RIGHT:
//        y1 = point.y();
//        x2 = point.x();
//        break;
//    case Utils::RECT_LEFT_MIDDLE:
//        x1 = point.x();
//        break;
//    case Utils::RECT_RIGHT_MIDDLE:
//        x2 = point.x();
//        break;
//    case Utils::RECT_BOTTOM_LEFT:
//        x1 = point.x();
//        y2 = point.y();
//        break;
//    case Utils::RECT_BOTTOM_MIDDLE:
//        y2 = point.y();
//        break;
//    case Utils::RECT_BOTTOM_RIGHT:
//        x2 = point.x();
//        y2 = point.y();
//        break;
//    }

//    float x = x1 < x2 ? x1 : x2;
//    float y = y1 < y2 ? y1 : y2;
//    float w = qAbs(x2 - x1);
//    float h = qAbs(y2 - y1);

//    if(w <2 ) w = 2;
//    if(h <2 ) h = 2;

//    QRect newBoundary(x,y,w,h);
//    this->m_shape->setBoundary(newBoundary);
//}
