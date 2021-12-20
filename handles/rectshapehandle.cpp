#include "rectshapehandle.h"
#include "screen/workspace.h"

RectShapeHandle::RectShapeHandle(RectLocator *locator):Handle(locator)
{
    m_anchor = locator->anchor();
}

void RectShapeHandle::flipAnchorX()
{
    Utils::RectAnchor newAnchor;

    switch(m_anchor) {
    case Utils::RECT_TOP_LEFT:
        newAnchor = Utils::RECT_TOP_RIGHT;
        break;
    case Utils::RECT_TOP_MIDDLE:
        newAnchor = m_anchor;
        break;
    case Utils::RECT_TOP_RIGHT:
        newAnchor = Utils::RECT_TOP_LEFT;
        break;
    case Utils::RECT_LEFT_MIDDLE:
        newAnchor = Utils::RECT_RIGHT_MIDDLE;
        break;
    case Utils::RECT_RIGHT_MIDDLE:
        newAnchor = Utils::RECT_LEFT_MIDDLE;
        break;
    case Utils::RECT_BOTTOM_LEFT:
        newAnchor = Utils::RECT_BOTTOM_RIGHT;
        break;
    case Utils::RECT_BOTTOM_MIDDLE:
        newAnchor = m_anchor;
        break;
    case Utils::RECT_BOTTOM_RIGHT:
        newAnchor = Utils::RECT_BOTTOM_LEFT;
        break;
    }

    m_anchor = newAnchor;

    RectLocator *rectLocator = dynamic_cast<RectLocator*>(m_locator);
    rectLocator->setAnchor(newAnchor);
}

void RectShapeHandle::flipAnchorY()
{
    Utils::RectAnchor newAnchor;

    switch(m_anchor) {
    case Utils::RECT_TOP_LEFT:
        newAnchor = Utils::RECT_BOTTOM_LEFT;
        break;
    case Utils::RECT_TOP_MIDDLE:
        newAnchor = Utils::RECT_BOTTOM_MIDDLE;
        break;
    case Utils::RECT_TOP_RIGHT:
        newAnchor = Utils::RECT_BOTTOM_RIGHT;
        break;
    case Utils::RECT_LEFT_MIDDLE:
        newAnchor = m_anchor;
        break;
    case Utils::RECT_RIGHT_MIDDLE:
        newAnchor = m_anchor;
        break;
    case Utils::RECT_BOTTOM_LEFT:
        newAnchor = Utils::RECT_TOP_LEFT;
        break;
    case Utils::RECT_BOTTOM_MIDDLE:
        newAnchor = Utils::RECT_TOP_MIDDLE;
        break;
    case Utils::RECT_BOTTOM_RIGHT:
        newAnchor = Utils::RECT_TOP_RIGHT;
        break;
    }

    m_anchor = newAnchor;

    RectLocator *rectLocator = dynamic_cast<RectLocator*>(m_locator);
    rectLocator->setAnchor(newAnchor);
}

void RectShapeHandle::setCursor(QWidget *targetUI)
{    
    switch(m_anchor) {
    case Utils::RECT_TOP_LEFT:
        targetUI->setCursor(Qt::SizeFDiagCursor);
        break;
    case Utils::RECT_TOP_MIDDLE:
        targetUI->setCursor(Qt::SizeVerCursor);
        break;
    case Utils::RECT_TOP_RIGHT:
        targetUI->setCursor(Qt::SizeBDiagCursor);
        break;
    case Utils::RECT_LEFT_MIDDLE:
        targetUI->setCursor(Qt::SizeHorCursor);
        break;
    case Utils::RECT_RIGHT_MIDDLE:
        targetUI->setCursor(Qt::SizeHorCursor);
        break;
    case Utils::RECT_BOTTOM_LEFT:
        targetUI->setCursor(Qt::SizeBDiagCursor);
        break;
    case Utils::RECT_BOTTOM_MIDDLE:
        targetUI->setCursor(Qt::SizeVerCursor);
        break;
    case Utils::RECT_BOTTOM_RIGHT:
        targetUI->setCursor(Qt::SizeFDiagCursor);
        break;
    }
}

