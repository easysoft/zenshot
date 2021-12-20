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
