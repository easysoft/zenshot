#include "screenlist.h"

#include <QCursor>
#include <QPainter>

ScreenList::ScreenList(QList<ScreenInfo> list)
{
    this->m_List = list;
    this->initParams();
}

QRect ScreenList::allBoundary(bool isGlobal) const
{
    if(isGlobal == true)
        return m_allBoundary;
    else
        return QRect(0,0,m_allBoundary.width(),m_allBoundary.height());
}

QPixmap ScreenList::allPixMap() const
{
    return m_allPixMap;
}

QRect ScreenList::boundaryAt(int screenIndex,bool isGlobal)
{
    if(isGlobal == true)
        return m_List[screenIndex].boundary;
    else
        return toLocal(m_List[screenIndex].boundary);
}

QScreen *ScreenList::screenAt(int screenIndex)
{
    return m_List[screenIndex].object;
}

QPixmap ScreenList::pixmapAt(int screenIndex)
{
    return m_List[screenIndex].pixmap;
}

int ScreenList::indexAtMouse()
{
    QPoint mousePos = QCursor::pos();
    int mCount = m_List.count();

    for(int i=0;i<mCount;i++)
    {
        if(m_List[i].boundary.contains(mousePos))
            return i;
    }

    return 0;
}

void ScreenList::initParams()
{
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;

    if(m_List.size() >0)
    {
        minX = m_List[0].boundary.x();
        minY = m_List[0].boundary.y();

        maxX = minX + m_List[0].boundary.width();
        maxY = minY + m_List[0].boundary.height();
    }

    for(int i=1;i<m_List.size();i++)
    {
        ScreenInfo info = m_List[i];

        minX = qMin(minX,info.boundary.x());
        maxX = qMax(maxX,info.boundary.x()+info.boundary.width());

        minY = qMin(minY,info.boundary.y());
        maxY = qMax(maxY,info.boundary.y()+info.boundary.height());
    }

    m_allBoundary.setRect(minX,minY, maxX-minX,maxY-minY);

    m_allPixMap = *new QPixmap(m_allBoundary.width(),m_allBoundary.height());
    QPainter painter(&m_allPixMap);

    for(ScreenInfo info:m_List)
    {
        QRect mRect = info.boundary;
        QPixmap mPixmap = info.pixmap;

        QRect rRect(mRect.x()-m_allBoundary.x(),mRect.y()-m_allBoundary.y(),mRect.width(),mRect.height());

        painter.drawPixmap(rRect,mPixmap);
    }
}

QRect ScreenList::toLocal(QRect rect)
{
    return QRect(rect.x()-m_allBoundary.x(),rect.y()-m_allBoundary.y(),rect.width(),rect.height());
}

void ScreenList::draw(QPainter &painter)
{
    painter.drawPixmap(allBoundary(),m_allPixMap);
}
