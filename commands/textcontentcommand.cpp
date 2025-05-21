/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "textcontentcommand.h"
#include "screen/workspace.h"

TextContentCommand::TextContentCommand(Workspace *workspace, std::shared_ptr<Text> shape,QString preContent):Command(workspace)
{
    this->m_shape = shape;
    m_oldContent = preContent;
    m_nowContent = m_shape->content();
}

void TextContentCommand::undo()
{
    m_shape->setContent(m_oldContent);
    m_workspace->refreshDraw();
}

void TextContentCommand::redo()
{
    m_shape->setContent(m_nowContent);
    m_workspace->refreshDraw();
}
