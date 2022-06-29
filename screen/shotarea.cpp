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

#include "shotarea.h"
#include "helper/windowgetter.h"
#include "screen/workspace.h"
#include "screen/shotarea/areahandle.h"
#include "core/gscale.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDesktopWidget>
#include <QPainterPath>
#include <QBrush>
#include <QtMath>

ShotArea::ShotArea(Workspace *workspace):RectShape(workspace),m_areaConfirmed(false)
{
    m_indicatorPen.setColor(QColor(151,151,151));
    m_indicatorPen.setWidth(1);
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

    QScreen *current = m_screenList->screenAt(m_nowScreenIndex);
    QSizeF physicalSize = current->physicalSize();
    QRect geometryRect = current->geometry();
    float pixel = current->physicalDotsPerInch();
    float scale = current->devicePixelRatio();
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

void ShotArea::drawMagnifier(QPainter &painter)
{
    GScale scale;  //modify temp for git push

    QRect pixBoundary = this->m_screenList->allBoundary();
    QPixmap pixPixmap = this->m_screenList->allPixMap();

    QImage bgImg = pixPixmap.toImage();
    QPoint mousePoint = QCursor::pos();

    QColor mouseColor = bgImg.pixel(mousePoint.x(),mousePoint.y());

    QString posStr = "POS: (" + QString::number(mousePoint.x()) + "," + QString::number(mousePoint.y()) + ")";
    QString rgbStr = "RGB: (" + QString::number(mouseColor.red()) + "," + QString::number(mouseColor.green()) + "," + QString::number(mouseColor.blue()) + ")";

    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(scale.ts(12));
    QFontMetrics fm(font);

    QRect posRect = fm.boundingRect(QRect(), 0, posStr);
    QRect rgbRect = fm.boundingRect(QRect(),0,"RGB: (255,255,255)");

    posRect.setHeight((int)((double)posRect.height() * 0.72));
    rgbRect.setHeight((int)((double)rgbRect.height() * 0.72));

    int hPadding = scale.ts( Utils::magnifier_text_h_padding);
    int vPadding = scale.ts( Utils::magnifier_text_v_padding);
    int textGap = scale.ts( Utils::magnifier_text_gap);

    int renderWidth = qMax(posRect.width(),rgbRect.width()) + hPadding * 2;
    int pixRenderHeight = (Utils::magnifier_from_height/Utils::magnifier_from_width) * renderWidth;
    int lblRenderHeight = posRect.height() + rgbRect.height() + textGap + vPadding * 2;
    int renderHeight = pixRenderHeight + lblRenderHeight;

    int pixSourceWidth = (int)((double)renderWidth / Utils::magnifier_zoom_ratio);
    int pixSourceHeight = (int)((double)pixRenderHeight / Utils::magnifier_zoom_ratio);

    QPoint baseOffset(scale.ts(10),scale.ts(40));

    QPoint basePos(mousePoint.x() + baseOffset.x(), mousePoint.y() + baseOffset.y());

    if(basePos.y() + renderHeight > pixBoundary.y() + pixBoundary.height())
    {
        basePos.setY(mousePoint.y() - baseOffset.y() - renderHeight);
    }

    if(basePos.x() + renderWidth > pixBoundary.x() + pixBoundary.width())
    {
        basePos.setX(mousePoint.x() - baseOffset.x() - renderWidth);
    }

    painter.save();

    QBrush whiteBrush;
    whiteBrush.setColor(Qt::white);
    whiteBrush.setStyle(Qt::SolidPattern);

    QBrush blackBrush;
    blackBrush.setColor(Qt::black);
    blackBrush.setStyle(Qt::SolidPattern);

    QPen borderPen;
    borderPen.setColor(Utils::magnifier_line_color);
    borderPen.setWidth(Utils::magnifier_border_width);

    QPen textPen;
    textPen.setColor(Qt::white);

    painter.setPen(borderPen);

    QRect pixRect(basePos.x(),basePos.y(),renderWidth,pixRenderHeight);
    painter.fillRect(pixRect,whiteBrush);
    painter.drawRect(pixRect);

    QRect lblRect(basePos.x(),basePos.y() + pixRenderHeight,renderWidth,lblRenderHeight);
    painter.fillRect(lblRect,blackBrush);

    painter.setFont(font);
    painter.setPen(textPen);

    painter.drawText(lblRect.x()+hPadding, lblRect.y() + vPadding + posRect.height() ,posStr);
    painter.drawText(lblRect.x()+hPadding, lblRect.y() + vPadding + posRect.height() + textGap + rgbRect.height() ,rgbStr);

    QRect sourceRect(mousePoint.x() - pixSourceWidth/2, mousePoint.y() - pixSourceHeight/2, pixSourceWidth, pixSourceHeight);
    if(sourceRect.x() + sourceRect.width() > pixBoundary.x() + pixBoundary.width())
        sourceRect.setX(pixBoundary.x() + pixBoundary.width() - sourceRect.width());
    else if(sourceRect.x() < pixBoundary.x())
        sourceRect.setX(pixBoundary.x());
    if(sourceRect.y() + sourceRect.height() > pixBoundary.y() + pixBoundary.height())
        sourceRect.setY(pixBoundary.y()+pixBoundary.height()-sourceRect.height());
    else if(sourceRect.y() < pixBoundary.y())
        sourceRect.setY(pixBoundary.y());

    painter.drawPixmap(pixRect,pixPixmap,sourceRect);

    QPen crossPen;
    crossPen.setColor(Utils::magnifier_line_color);
    crossPen.setWidth(Utils::magnifier_cross_width);
    painter.setPen(crossPen);

    int shrink = Utils::magnifier_cross_width/2;
    painter.drawLine(pixRect.x()+shrink, pixRect.y()+pixRect.height()/2, pixRect.x()+pixRect.width()-shrink, pixRect.y()+pixRect.height()/2);
    painter.drawLine(pixRect.x()+pixRect.width()/2, pixRect.y()+shrink, pixRect.x()+pixRect.width()/2, pixRect.y()+pixRect.height()-shrink);

    painter.restore();
}

void ShotArea::draw(QPainter &painter)
{
    if(m_selected == false)
        m_indicatorPen.setWidth(1);
    else
        m_indicatorPen.setWidth(1);

    painter.save();

    //绘制底图
    //m_screenList->draw(painter);

    //初始化遮罩
    QPainterPath maskPath;
    maskPath.addRect(m_screenList->allBoundary());
    maskPath.addRect(m_boundary);

    QBrush maskBrush;
    maskBrush.setColor(QColor(0,0,0,150));
    maskBrush.setStyle(Qt::SolidPattern);


    //painter.fillPath(maskPath,maskBrush);

    //绘制底图
    m_screenList->draw(painter,maskPath,maskBrush);

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

    //如未确定选择区域，绘制放大镜提示
    if(m_areaConfirmed == false)
    {
        drawMagnifier(painter);
    }

    painter.restore();
}

void ShotArea::loadPropsImpl(Store *store)
{

}

void ShotArea::savePropsImpl(Store *store)
{

}


