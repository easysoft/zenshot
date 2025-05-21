/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "core/handle.h"
#include "core/utils.h"

#include <QPen>
#include <QBrush>
#include <QPoint>

Handle::Handle(Locator *locator)
{
    this->m_locator = locator;
}

Locator *Handle::locator() const
{
    return m_locator;
}

QRect Handle::boundary()
{
    int size = Utils::Handle_Shape_Size;
    QPoint center = m_locator->location();
    QRect rect(center.x()-size/2, center.y()-size/2, size, size);

    return  rect;
}

bool Handle::contain(QPointF point)
{
    QRectF mBoundary = boundary();
    return  mBoundary.contains(point.x(),point.y());
}

void Handle::move(QPoint point)
{
    m_locator->setLocation(point);
}

void Handle::draw(QPainter &painter)
{
    painter.save();

    QPen pen;
    pen.setColor(Utils::Handle_Shape_Border_Color);
    pen.setWidth(Utils::Handle_Shape_Border_Thickness);

    QBrush brush;
    brush.setColor(Utils::Handle_Shape_Fill_Color);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);

    QRectF mBoundary = boundary();

    painter.drawEllipse(mBoundary);

    painter.restore();
}

void Handle::setCursor(QWidget *targetUI)
{
    targetUI->setCursor(Qt::SizeAllCursor);
}

