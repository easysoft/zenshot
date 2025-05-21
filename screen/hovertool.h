/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef HITTOOL_H
#define HITTOOL_H

#include "core/tool.h"
#include "core/handle.h"
#include "core/shape.h"

/**
 * @class : HoverTool
 * @brief : 悬停工具类定义
 * @note  : 鼠标悬停辅助工具类定义
 */
class HoverTool : public Tool
{
public:
    explicit HoverTool(Workspace *m_workspace);

public:

    /**
     * @brief 获取可被命中图形上的控制手柄
     * @return
     */
    Handle *shapeHandle() const;

    /**
     * @brief 获取可被命中截图区域上的控制手柄
     * @return
     */
    Handle *shotAeaHandle() const;

    /**
     * @brief 获取可被命中的图形
     * @return
     */
    std::shared_ptr<Shape> shape() const;

    /**
     * @brief 获取截图区域本身是否可被命中
     * @return
     */
    bool shotAreaSelf() const;

    /**
     * @brief 根据给定坐标重新判断可被命中的元素
     * @param mousePoint
     */
    void refresh(QPoint mousePoint);

    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    bool m_shotAreaSelf;
    std::shared_ptr<Shape> m_shape;
    Handle *m_shapeHandle;
    Handle *m_shotAreaHandle;

    void setCursor(QPoint mousePoint);
};

#endif // HITTOOL_H
