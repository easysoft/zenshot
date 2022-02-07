/* Copyright (C) 2021 Nature Easy Soft Network Technology Co., LTD
 *
 * This file is part of Zenshot (https://github.com/easysoft/zenshot/).
 *
 * Zenshot is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zenshot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zenshot. If not, see <https://www.gnu.org/licenses/>.
 */

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
