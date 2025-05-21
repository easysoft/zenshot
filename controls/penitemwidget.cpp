/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "penitemwidget.h"

#include <QPainter>

PenItemWidget::PenItemWidget(Qt::PenStyle penStyle, QWidget *parent):QLabel(parent)
{
    this->m_penStyle = penStyle;
    this->m_renderer = new PenRenderer(this,penStyle,5,5);
}

PenItemWidget::~PenItemWidget()
{
    delete m_renderer;
    m_renderer = nullptr;
}

Qt::PenStyle PenItemWidget::penStyle() const
{
    return m_penStyle;
}

void PenItemWidget::paintEvent(QPaintEvent *event)
{
    m_renderer->draw();
}
