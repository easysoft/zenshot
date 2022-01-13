#ifndef APPINSTALL_H
#define APPINSTALL_H

#include <QObject>

#include "widget.h"

class Starter : public QObject
{
    Q_OBJECT
public:
    Starter();

    void init(QWidget *parent=nullptr);

private:
    QList<Widget*> *m_widgets;

private slots:
    void close(int code);
    void finishConfirmArea();
};


#endif // APPINSTALL_H
