/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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
    std::shared_ptr<Text> m_shape;
};

#endif // TEXTTOOL_H
