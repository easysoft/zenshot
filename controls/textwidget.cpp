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

#include "textwidget.h"
#include "core/utils.h"
#include <QPainter>

TextWidget::TextWidget(QWidget *parent):QDialog(parent, Qt::SplashScreen | Qt::FramelessWindowHint)
{
    setAttribute(Qt::WA_TranslucentBackground);
    m_textImpl = new TextWidgetImpl(this);
    m_textImpl->move(Utils::TextEdit_Padding_Horizontal,Utils::TextEdit_Padding_Vertical);
    connect(m_textImpl, SIGNAL(sizeChanged(QSize)), this, SLOT(onContentSizeChanged(QSize)));
}

void TextWidget::setTextColor(QColor color)
{
    m_textImpl->setTextColor(color);
}

void TextWidget::makeFocus()
{
    m_textImpl->setFocus();
}

QString TextWidget::text()
{
    return m_textImpl->toPlainText();
}

void TextWidget::setText(QString text)
{
    m_textImpl->setText(text);
}

void TextWidget::setFont(const QFont &f)
{
    m_textImpl->setFont(f);
}

void TextWidget::onContentSizeChanged(QSize size)
{
    this->setFixedSize(size.width()+Utils::TextEdit_Padding_Horizontal*2,
                       size.height()+Utils::TextEdit_Padding_Vertical*2);
}

void TextWidget::hideEvent(QHideEvent* event)
{
    m_textImpl->setText(u8"");
    QWidget::hideEvent(event);
}

void TextWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    QSize mSize = size();
    QRect realRect(Utils::Handle_AntLine_Thicknes,
                   Utils::Handle_AntLine_Thicknes,
                   mSize.width()-Utils::Handle_AntLine_Thicknes*2,
                   mSize.height()-Utils::Handle_AntLine_Thicknes*2);

    QPen baseIndicator;
    baseIndicator.setColor(Utils::Handle_AntLine_SubColor);
    baseIndicator.setWidth(Utils::Handle_AntLine_Thicknes);

    painter.setPen(baseIndicator);
    painter.drawRect(realRect);

    QPen indicator;
    indicator.setColor(Utils::Handle_AntLine_Color);
    indicator.setWidth(Utils::Handle_AntLine_Thicknes);
    indicator.setStyle(Qt::DashLine);

    painter.setPen(indicator);
    painter.drawRect(realRect);
}
