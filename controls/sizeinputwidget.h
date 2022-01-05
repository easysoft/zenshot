#ifndef SIZEINPUTWIDGET_H
#define SIZEINPUTWIDGET_H

#include <QWidget>
#include <QSpinBox>

#include "core/gscale.h"

class SizeInputWidget : public QWidget,GScale
{
    Q_OBJECT
public:
    SizeInputWidget(QWidget *parent=nullptr);

    int value() const;
    void setValue(int value);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int m_minSize;
    int m_maxSize;

    QSpinBox *m_inpputBox;

signals:
    void sizeChanged();

private slots:
    void onInpputIntChanged(int);
};

#endif // SIZEINPUTWIDGET_H
