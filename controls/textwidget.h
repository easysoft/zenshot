#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>

#include "controls/textwidgetimpl.h"

class TextWidget : public QWidget
{
    Q_OBJECT
public:
    TextWidget(QWidget *parent=nullptr);

    QString text();
    void setText(QString text);

    void setFont(const QFont& f);
    void setTextColor(const QColor c);

    void makeFocus();

protected:
    void paintEvent(QPaintEvent *event);

private:
    TextWidgetImpl * m_textImpl;

private slots:
    void onContentSizeChanged(QSize size);

};

#endif // TEXTWIDGET_H
