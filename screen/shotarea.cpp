#include "shotarea.h"
#include "helper/windowgetter.h"
#include "screen/workspace.h"
#include "screen/shotarea/areahandle.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDesktopWidget>
#include <QPainterPath>
#include <QBrush>

ShotArea::ShotArea(Workspace *workspace):RectShape(workspace),m_areaConfirmed(false)
{
    m_indicatorPen.setColor(QColor(255,255,255));
    m_indicatorPen.setWidth(3);
    m_isGettingResult = false;
}

ShotArea::~ShotArea()
{
    delete m_screenList;
    m_screenList = nullptr;

    qDeleteAll(m_handles);
    m_handles.clear();
}

QRect ShotArea::allBoundary()
{
    return m_allScreenRect;
}

QPixmap ShotArea::allPixmap() const
{
    return m_screenList->allPixMap();
}

QRect ShotArea::areaBoundary()
{
    return boundary();
}

bool ShotArea::areaConfirmed()
{
    return m_areaConfirmed;
}

void ShotArea::start(ScreenList *list)
{
    m_screenList = list;
    m_allScreenRect = m_screenList->allBoundary();

    autoCapture();
}

void ShotArea::autoCapture()
{
    autoCaptureScreen();
    autoCaptureWindow();
}


void ShotArea::autoCaptureScreen()
{
    //获取鼠标所在位置的屏幕
    m_nowScreenIndex = m_screenList->indexAtMouse();
}

void ShotArea::autoCaptureWindow()
{
    QWidget *host = m_workspace->widget();
    //初始化选择区域
    QRect globalArea = WindowGetter::winGeometry(m_screenList->screenAt(m_nowScreenIndex),host);
    QRect area = m_screenList->toLocal(globalArea);
    m_boundary.setRect(area.x(),area.y(),area.width(),area.height());

    //根据屏幕大小来进一步约束选择区域
    int x1 = m_boundary.x() < m_allScreenRect.x() ? m_allScreenRect.x() : m_boundary.x();
    int y1 = m_boundary.y() < m_allScreenRect.y() ? m_allScreenRect.y() : m_boundary.y();

    int x2 = m_boundary.right() > m_allScreenRect.right() ? m_allScreenRect.right() : m_boundary.right();
    int y2 = m_boundary.bottom() > m_allScreenRect.bottom() ? m_allScreenRect.bottom() : m_boundary.bottom();

    m_boundary.setRect(x1,y1,x2-x1,y2-y1);
}

void ShotArea::confirmArea()
{
    m_handles = this->handles();
    setSelected(true);
    m_areaConfirmed = true;
}

Handle *ShotArea::handleAt(QPoint point)
{
    for(Handle* hdle:m_handles)
    {
        if(hdle->contain(point) == true)
            return  hdle;
    }

    return nullptr;
}

QPixmap ShotArea::result()
{
    m_isGettingResult = true;

    QRectF mBoundary = boundary();

    QPixmap tmpPixmap(m_allScreenRect.width(),m_allScreenRect.height());

    QPainter tmpPainter(&tmpPixmap);
    tmpPainter.drawPixmap(m_allScreenRect,m_screenList->allPixMap());

    m_workspace->draw(tmpPainter);

    QPixmap result(mBoundary.width(),mBoundary.height());
    QPainter resultPainter(&result);
    resultPainter.drawPixmap(QRect(0,0,mBoundary.width(),mBoundary.height()),tmpPixmap,mBoundary);

    m_isGettingResult = false;

    return  result;
}

QVector<Handle *> ShotArea::handles()
{
    if(m_handles.size() > 0)
        return m_handles;

    QVector<Handle*> results;

    AreaLocator *topLeft = new AreaLocator(this,Utils::RECT_TOP_LEFT);
    AreaHandle *topLeftHandle = new AreaHandle(topLeft);
    results.append(topLeftHandle);

    AreaLocator *topMiddle = new AreaLocator(this,Utils::RECT_TOP_MIDDLE);
    AreaHandle *topMiddleHandle = new AreaHandle(topMiddle);
    results.append(topMiddleHandle);

    AreaLocator *topRight = new AreaLocator(this,Utils::RECT_TOP_RIGHT);
    AreaHandle *topRightHandle = new AreaHandle(topRight);
    results.append(topRightHandle);

    AreaLocator *leftMiddle = new AreaLocator(this,Utils::RECT_LEFT_MIDDLE);
    AreaHandle *leftMiddleHandle = new AreaHandle(leftMiddle);
    results.append(leftMiddleHandle);

    AreaLocator *rightMiddle = new AreaLocator(this,Utils::RECT_RIGHT_MIDDLE);
    AreaHandle *rightMiddleHandle = new AreaHandle(rightMiddle);
    results.append(rightMiddleHandle);


    AreaLocator *bottomLeft = new AreaLocator(this,Utils::RECT_BOTTOM_LEFT);
    AreaHandle *bottomLeftHandle = new AreaHandle(bottomLeft);
    results.append(bottomLeftHandle);

    AreaLocator *bottomMiddle = new AreaLocator(this,Utils::RECT_BOTTOM_MIDDLE);
    AreaHandle *bottomMiddleHandle = new AreaHandle(bottomMiddle);
    results.append(bottomMiddleHandle);

    AreaLocator *bottomRight = new AreaLocator(this,Utils::RECT_BOTTOM_RIGHT);
    AreaHandle *bottomRightHandle = new AreaHandle(bottomRight);
    results.append(bottomRightHandle);


    return  results;
}

void ShotArea::draw(QPainter &painter)
{
    if(m_selected == false)
        m_indicatorPen.setWidth(3);
    else
        m_indicatorPen.setWidth(1);

    painter.save();

    //绘制底图
    m_screenList->draw(painter);

    //绘制遮罩
    QPainterPath maskPath;
    maskPath.addRect(m_screenList->allBoundary());
    maskPath.addRect(m_boundary);

    QBrush maskBrush;
    maskBrush.setColor(QColor(0,0,0,150));
    maskBrush.setStyle(Qt::SolidPattern);

    painter.fillPath(maskPath,maskBrush);

    if(m_isGettingResult == false)
    {
        QRect rect(m_boundary.x(),
                   m_boundary.y(),
                   m_boundary.width(),
                   m_boundary.height());

        //绘制选择区域边界指示器
        painter.setPen(m_indicatorPen);
        painter.drawRect(rect);

        //绘制控制手柄
        foreach(Handle* hdle, m_handles)
        {
            hdle->draw(painter);
        }
    }

    painter.restore();
}

void ShotArea::loadPropsImpl(Store *store)
{

}

void ShotArea::savePropsImpl(Store *store)
{

}


