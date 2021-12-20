#ifndef WORKAREACREATETOOL_H
#define WORKAREACREATETOOL_H

#include "core/tool.h"
#include <QRect>
#include <QPoint>

/**
 * @class : AreaCreateTool
 * @brief : 截图区域创建工具
 * @note  : 截图区域创建工具
 */
class AreaCreateTool : public Tool
{
public:
    explicit AreaCreateTool(Workspace *m_workspace);

    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint,QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);


private:
    bool m_isMousePress;
    QPoint m_startPoint;
};

#endif // WORKAREACREATETOOL_H
