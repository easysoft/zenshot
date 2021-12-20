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
    indicator.setStyle(Qt::DashLine);

    painter.setPen(indicator);
    painter.drawRect(realRect);

    painter.restore();
}


