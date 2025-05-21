/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef PENITEMWIDGET_H
#define PENITEMWIDGET_H

#include <QLabel>

#include "controls/penrenderer.h"

class PenItemWidget : public QLabel
{
public:
    PenItemWidget(Qt::PenStyle penStyle, QWidget *parent = nullptr);
    ~PenItemWidget();

    Qt::PenStyle penStyle() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    PenRenderer * m_renderer;
    Qt::PenStyle m_penStyle;
};

#endif // PENITEMWIDGET_H
