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

#ifndef MOSAIC_H
#define MOSAIC_H

#include "core/pointshape.h"

class Mosaic : public PointsShape
{
public:
    explicit Mosaic(Workspace *m_workspace);

    QString type();
    QRect boundary();
    QVector<Handle *> handles();
    void draw(QPainter &painter);
    bool contain(QPoint point);

protected:
    void loadPropsImpl(Store *store);
    void savePropsImpl(Store *store);

private:
    QVector<QRect> getRects();    
};

#endif // MOSAIC_H
