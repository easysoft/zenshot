#ifndef LINECREATETOOL_H
#define LINECREATETOOL_H

#include "core/tool.h"
#include "shapes/line.h"

class LineCreateTool : public Tool
{
public:
    explicit LineCreateTool(Workspace *m_workspace);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    Line *m_shape;
    bool m_isInlist;

};

#endif // LINECREATETOOL_H
