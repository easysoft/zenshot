/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "areahandle.h"
#include "core/utils.h"

AreaHandle::AreaHandle(AreaLocator *locator):Handle(locator)
{
    m_anchor = locator->anchor();
}

QRect AreaHandle::boundary()
{
    int size = Utils::Handle_Area_Size;
    QPoint center = m_locator->location();
    QRect rect(center.x()-size/2, center.y()-size/2, size, size);

    return  rect;
}

void AreaHandle::flipAnchorX()
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

    AreaLocator *areaLocator = dynamic_cast<AreaLocator*>(m_locator);
    areaLocator->setAnchor(newAnchor);
}

void AreaHandle::flipAnchorY()
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

    AreaLocator *areaLocator = dynamic_cast<AreaLocator*>(m_locator);
    areaLocator->setAnchor(newAnchor);
}

void AreaHandle::setCursor(QWidget *targetUI)
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

void AreaHandle::draw(QPainter &painter)
{
    painter.save();

    QPen pen;
    pen.setColor(Utils::Handle_Area_Border_Color);
    pen.setWidth(Utils::Handle_Area_Border_Thickness);

    QBrush brush;
    brush.setColor(Utils::Handle_Area_Fill_Color);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);

    QRectF mBoundary = boundary();

    painter.drawEllipse(mBoundary);

    painter.restore();
}
