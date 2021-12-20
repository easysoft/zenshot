#ifndef PENRENDERER_H
#define PENRENDERER_H

#include <QWidget>
#include <QColor>

class PenRenderer
{
public: 
    PenRenderer(QWidget *widget,Qt::PenStyle penStyle, int marginLeft,int marginRight);

    void draw();

    Qt::PenStyle penStyle() const;
    void setPenStyle(const Qt::PenStyle &penStyle);

private:
    QWidget *m_widget;

    int m_marginLeft;
    int m_marginRight;

    int m_lineWidth;
    QColor m_lineColor;
    Qt::PenStyle m_penStyle;


};

#endif // PENRENDERER_H
