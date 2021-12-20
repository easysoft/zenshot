#ifndef AREAMOVETOOL_H
#define AREAMOVETOOL_H

#include "core/tool.h"

/**
 * @class : AreaMoveTool
 * @brief : 截图区域移动工具类
 * @note  : 截图区域移动工具类
 */
class AreaMoveTool : public Tool
{
public:
    explicit AreaMoveTool(Workspace *m_workspace);

    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);
};

#endif // AREAMOVETOOL_H
