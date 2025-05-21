/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "shape.h"
#include "stores/localstore.h"

#include "spdlogwrapper.hpp"

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
        L_INFO("{0} @ {1} IS NULL", __FUNCTION__, __LINE__);
        LocalStore *local = new LocalStore();
        loadPropsImpl(local);
    }
    else
    {
        L_INFO("{0} @ {1} NOT NULL", __FUNCTION__, __LINE__);
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


