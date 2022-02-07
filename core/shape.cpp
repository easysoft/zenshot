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

#include "shape.h"
#include "stores/localstore.h"

Shape::Shape(Workspace *workspace)
{
    m_selected = false;
    this->m_workspace = workspace;
}

QString Shape::type()
{
    return "base";
}

Workspace* Shape::workspace()
{
    return m_workspace;
}

bool Shape::selected()
{
    return m_selected;
}

void Shape::setSelected(bool flag)
{
    m_selected = flag;
}

void Shape::loadProps(Store *store)
{
    if(store == nullptr)
    {
        LocalStore *local = new LocalStore();
        loadPropsImpl(local);
    }
    else
    {
        loadPropsImpl(store);
    }
}

void Shape::saveProps(Store *store)
{
    if(store == nullptr)
    {
        LocalStore *local = new LocalStore();
        savePropsImpl(local);
    }
    else
    {
        savePropsImpl(store);
    }
}

void Shape::drawAntIndicator(QPainter &painter, QRect rect,float extend)
{
    painter.save();

    int ext = extend + Utils::Handle_AntLine_Thicknes;

    QRect realRect(rect.x()-ext,rect.y()-ext,rect.width()+ext*2,rect.height()+ext*2);

    QPen baseIndicator;
    baseIndicator.setColor(Utils::Handle_AntLine_SubColor);
    baseIndicator.setWidth(Utils::Handle_AntLine_Thicknes);

    painter.setPen(baseIndicator);
    painter.drawRect(realRect);

    QPen indicator;
    indicator.setColor(Utils::Handle_AntLine_Color);
    indicator.setWidth(Utils::Handle_AntLine_Thicknes);
    indicator.setStyle(Qt::CustomDashLine);
    indicator.setDashPattern(QVector<qreal>{3,3});

    painter.setPen(indicator);
    painter.drawRect(realRect);

    painter.restore();
}


