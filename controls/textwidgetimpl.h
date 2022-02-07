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
