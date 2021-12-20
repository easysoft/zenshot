#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <screen/workspace.h>
#include <QPixmap>
#include <QPainter>

#include "core/screenlist.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(ScreenList *list, QWidget *parent = nullptr);
    ~Widget();

    Workspace* workspace() const;
    void finishConfirmArea();

private:
    QString m_status;  //unknown, active, giveup
    Workspace *m_workspace;

    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void paintEvent(QPaintEvent *);
};

#endif // WIDGET_H
