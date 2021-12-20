#ifndef TEXTWIDGETIMPL_H
#define TEXTWIDGETIMPL_H

#include <QTextEdit>
#include <QSize>

/**
 * @class : TextWidgetImpl
 * @brief : 文本编辑类定义
 * @note  : 高宽自动调整的文本编辑
 */
class TextWidgetImpl : public QTextEdit
{
    Q_OBJECT

public:
    explicit TextWidgetImpl(QWidget* parent = nullptr);

    QSize desireSize();
    void adjustSize();
    void setFont(const QFont& f);
    void setTextColor(const QColor& c);

protected:
    void showEvent(QShowEvent* e);
    void resizeEvent(QResizeEvent* e);

signals:
    void textUpdated(const QString& s);
    void sizeChanged(QSize size);

private slots:
    void emitTextUpdated();    
};

#endif // TEXTWIDGETIMPL_H
