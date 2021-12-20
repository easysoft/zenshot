#ifndef TEXTTOOL_H
#define TEXTTOOL_H

#include "shapes/text.h"
#include "core/tool.h"

class TextAssist;

class TextCreateTool : public Tool
{
public:
    explicit TextCreateTool(Workspace *m_workspace);

    QString forType();
    void onMousePress(QPoint mousePoint);
    void onMouseMove(QPoint mousePoint, QPoint mouseOffset);
    void onMouseRelease(QPoint mousePoint);

private:
    Text *m_shape;
};

#endif // TEXTTOOL_H
