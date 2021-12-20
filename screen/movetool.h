#ifndef MOVETOOL_H
#define MOVETOOL_H

#include <QPoint>

#include "core/tool.h"
#include "core/shape.h"

/**
 * @class : MoveTool
 * @brief : 移动工具类定义
 * @note  : 提供移动图形功能
 */
class MoveTool : public Tool
{
public:
    explicit MoveTool(Workspace *m_workspace,Shape *m_shape);

private:
    Shape *m_shape;

    QPoint m_start;  //鼠标移动的起始点
    QPoint m_end;    //鼠标移动的结束点

public:
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);
};

#endif // MOVETOOL_H
