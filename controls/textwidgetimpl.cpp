#include "textwidgetimpl.h"
#include "core/utils.h"

#include <QTextFrame>
#include <QPainter>

TextWidgetImpl::TextWidgetImpl(QWidget* parent):QTextEdit(parent)
{
    QString sheet(
         "TextWidgetImpl { background: transparent; border:0px solid transparent; padding:0px 0px 0px 0px; }");

    setStyleSheet(sheet);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setContextMenuPolicy(Qt::NoContextMenu);

    connect(this, &TextWidgetImpl::cursorPositionChanged, this, &TextWidgetImpl::adjustSize);
    connect(this, &TextWidgetImpl::textChanged, this, &TextWidgetImpl::emitTextUpdated);
}

void TextWidgetImpl::showEvent(QShowEvent* e)
{
    QTextEdit::showEvent(e);
    adjustSize();
}

void TextWidgetImpl::resizeEvent(QResizeEvent* e)
{
    QTextEdit::resizeEvent(e);
}

void TextWidgetImpl::setFont(const QFont& f)
{
    QTextEdit::setFont(f);
    adjustSize();
}

void TextWidgetImpl::setTextColor(const QColor& c)
{
    //QTextEdit::setTextColor(c);
    QString sheet(
         "TextWidgetImpl { background: transparent; border:0px solid transparent; padding:0px 0px 0px 0px; color:rgba(%1, %2, %3, %4); }");

    setStyleSheet(sheet.arg(c.red()).arg(c.green()).arg(c.blue()).arg(c.alpha()));
}

QSize TextWidgetImpl::desireSize()
{
    QString text = this->toPlainText();

    QFontMetrics fm(font());

    QRect bounds = fm.boundingRect(QRect(), 0, text);
    int pixelsWide = bounds.width()  + 100;
    int pixelsHigh = bounds.height() + fm.height()*Utils::TextEdit_Height_Extend;

    return  QSize(pixelsWide,pixelsHigh);
}

void TextWidgetImpl::adjustSize()
{
    QSize size = desireSize();
    this->setFixedSize(size.width(),size.height());
    emit sizeChanged(size);
}

void TextWidgetImpl::emitTextUpdated()
{
    emit textUpdated(this->toPlainText());
}
