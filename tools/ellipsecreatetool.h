#ifndef ELLIPSECREATETOOL_H
#define ELLIPSECREATETOOL_H

#include "core/tool.h"
#include "shapes/ellipse.h"

class EllipseCreateTool : public Tool
{
public:
    explicit EllipseCreateTool(Workspace *m_workspace);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    Ellipse *m_shape;
    QPoint m_startPoint;
    QPoint m_endPoint;
    bool m_isInlist;
};

#endif // ELLIPSECREATETOOL_H
