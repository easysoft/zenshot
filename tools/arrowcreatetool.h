#ifndef ARROWCREATETOOL_H
#define ARROWCREATETOOL_H

#include "core/tool.h"
#include "shapes/arrow.h"

class ArrowCreateTool : public Tool
{
public:
    explicit ArrowCreateTool(Workspace *m_workspace);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    Arrow *m_shape;
    bool m_isInlist;
};

#endif // ARROWCREATETOOL_H
