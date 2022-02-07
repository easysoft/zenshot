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

#ifndef TEXT_H
#define TEXT_H

#include "core/shape.h"

class Text : public Shape
{
public:
    explicit Text(Workspace *m_workspace);

public:
    QString type();
    void move(QPoint offsetPoint);
    QVector<Handle *> handles();
    QRect boundary();
    void draw(QPainter &painter);
    bool contain(QPoint point);

    QFont font();

    QString content() const;
    void setContent(const QString &value);

    QColor color() const;
    void setColor(const QColor &color);

    QPoint location() const;
    void setLocation(const QPoint &value);

protected:
    void loadPropsImpl(Store *store);
    void savePropsImpl(Store *store);

private:
    int m_size;
    bool m_italic;
    bool m_underline;
    int m_weight;
    QString m_family;
    QColor m_color;

    QPoint m_location;
    QString m_content;

};

#endif // TEXT_H
