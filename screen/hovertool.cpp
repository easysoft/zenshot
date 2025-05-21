/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "hovertool.h"

#include "spdlogwrapper.hpp"

#include "screen/workspace.h"
#include "core/utils.h"

HoverTool::HoverTool(Workspace *workspace):Tool(workspace),m_shotAreaSelf(false)
{
    L_INFO("{0}, {1}", __FUNCTION__, __LINE__);
}

Handle *HoverTool::shapeHandle() const
{
    return m_shapeHandle;
}

Handle *HoverTool::shotAeaHandle() const
{
    return m_shotAreaHandle;
}

std::shared_ptr<Shape> HoverTool::shape() const
{
    return m_shape;
}

bool HoverTool::shotAreaSelf() const
{
    return m_shotAreaSelf;
}

void HoverTool::refresh(QPoint mousePoint)
{
    m_shapeHandle = nullptr;
    m_shotAreaHandle = nullptr;
    m_shape = nullptr;
    m_shotAreaSelf = false;

    //1）获取鼠标拾取到用户绘制图形的控制手柄
    m_shapeHandle = m_workspace->getShapeHandleAt(mousePoint);
    //2）如果第一步没有获取到，进一步获取截图区域的控制手柄
    if(m_shapeHandle == nullptr)
    {
        m_shotAreaHandle = m_workspace->getShotAreaHandleAt(mousePoint);
    }
    //3)如果第1第2不没有获取到，进一步获取用户绘制的图形
    if(m_shapeHandle == nullptr && m_shotAreaHandle == nullptr)
    {
        m_shape = m_workspace->getShapeAt(mousePoint);
    }
    //4)如果上面的都没有获取到，最后判断是否获取到截图区域本身
    if(m_shapeHandle == nullptr && m_shotAreaHandle == nullptr && m_shape == nullptr)
    {
        m_shotAreaSelf = m_workspace->isShotAreaSelfAt(mousePoint);
    }

    //选中马赛克工具后，不允许选中其他图形
    Tool *createTool = m_workspace->createTool();
    if(createTool != nullptr && createTool->forType() == Utils::forMosaicKey())
    {
        m_shapeHandle = nullptr;
        m_shotAreaHandle = nullptr;
        m_shape = nullptr;
        m_shotAreaSelf = false;
    }
}

void HoverTool::setCursor(QPoint mousePoint)
{
    if(m_shapeHandle != nullptr)
    {
        m_shapeHandle->setCursor(m_workspace->widget());
    }
    else if(m_shotAreaHandle != nullptr)
    {
        m_shotAreaHandle->setCursor(m_workspace->widget());
    }
    else if(m_shape != nullptr)
    {
        m_workspace->widget()->setCursor(Qt::SizeAllCursor);
    }
    else if(m_shotAreaSelf == true && m_workspace->hasCreateTool() == false)
    {
        m_workspace->widget()->setCursor(Qt::SizeAllCursor);
    }
    else
    {
        Tool *createTool = m_workspace->createTool();
        if(createTool != nullptr)
        {
            QRectF shotArea = m_workspace->areaBoundary();
            if(shotArea.contains(mousePoint))
                createTool->setCursor();
            else
                m_workspace->widget()->setCursor(Qt::ArrowCursor);
        }
        else
        {
            m_workspace->widget()->setCursor(Qt::ArrowCursor);
        }
    }
}


void HoverTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    L_FUNCTION();

    refresh(mousePoint);
    setCursor(mousePoint);
}


void HoverTool::onMousePress(QPoint mousePoint)
{

}

void HoverTool::onMouseRelease(QPoint mousePoint)
{

}
