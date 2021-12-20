#ifndef RECTCREATETOOL_H
#define RECTCREATETOOL_H

#include "core/tool.h"
#include "shapes/rectangle.h"

class RectCreateTool : public Tool
{
public:
    RectCreateTool(Workspace *m_workspace);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    Rectangle *m_shape;
    QPoint m_startPoint;
    QPoint m_endPoint;
    bool m_isInlist;

};

#endif // RECTCREATETOOL_H
