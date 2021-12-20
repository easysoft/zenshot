#ifndef MOSAICCREATETOOL_H
#define MOSAICCREATETOOL_H

#include "core/tool.h"
#include "shapes/mosaic.h"

class MosaicCreateTool : public Tool
{
public:
    explicit MosaicCreateTool(Workspace *m_workspace);

    QString forType();
    void setCursor();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    Mosaic *m_shape;
};

#endif // MOSAICCREATETOOL_H
