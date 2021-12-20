#ifndef CURVECREATETOOL_H
#define CURVECREATETOOL_H

#include "core/tool.h"
#include "shapes/curve.h"

class CurveCreateTool : public Tool
{
public:
    explicit CurveCreateTool(Workspace *m_workspace);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    Curve *m_shape;

};

#endif // CURVECREATETOOL_H
