#include "areacreatetool.h"
#include "screen/helper/windowgetter.h"
#include "screen/shotarea.h"
#include "screen/workspace.h"
#include <QtCore/QtMath>

AreaCreateTool::AreaCreateTool(Workspace *wordspace):Tool(wordspace),m_isMousePress(false)
{

}

void AreaCreateTool::onMousePress(QPoint mousePoint)
{
    m_isMousePress = true;
    m_startPoint = mousePoint;
}

void AreaCreateTool::onMouseMove(QPoint mousePoint,QPoint mouseOffset)
{
    if(m_isMousePress == false)
    {
        m_workspace->autoCapture();
        m_workspace->refreshDraw();
    }
    else
    {
        //鼠标左键按下，执行手动框区域操作
        QPoint endPoint = mousePoint;

        int x = m_startPoint.x() < endPoint.x() ? m_startPoint.x() : endPoint.x();
        int y = m_startPoint.y() < endPoint.y() ? m_startPoint.y() : endPoint.y();

        int w = qAbs(m_startPoint.x() - endPoint.x());
        int h = qAbs(m_startPoint.y() - endPoint.y());

        QRect rect(x,y,w,h);
        m_workspace->setAreaBoundary(rect);
        m_workspace->refreshDraw();
    }
}

void AreaCreateTool::onMouseRelease(QPoint mousePoint)
{
    //确定选择区域
    m_workspace->confirmArea();
}
