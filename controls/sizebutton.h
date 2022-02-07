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

#ifndef SIZEBUTTON_H
#define SIZEBUTTON_H

#include <QWidget>
#include <QAbstractButton>
#include <QPushButton>
#include <QColor>
#include <QBrush>

/**
 * @class : SizeButton
 * @brief : 大小按钮类定义
 * @note  : 表示尺寸的按钮
 */
class SizeButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit SizeButton(QWidget *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    int radius() const;
    void setRadius(int radius);

    int value() const;
    void setValue(int value);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    int m_padding;
    int m_radius;
    int m_value;
    QColor m_color;

    bool m_isHovered;

    int m_borderWidth;
    QColor m_borderColor;
    QColor m_backgroundColor;

    int m_hovered_borderWidth;
    QColor m_hovered_borderColor;
    QColor m_hovered_backgroundColor;

    int m_checked_borderWidth;
    QColor m_checked_borderColor;
    QColor m_checked_backgroundColor;
};

#endif // SIZEBUTTON_H
