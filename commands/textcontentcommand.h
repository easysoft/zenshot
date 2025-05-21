/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef TEXTCONTENTCOMMAND_H
#define TEXTCONTENTCOMMAND_H

#include "core/command.h"
#include "shapes/text.h"

/**
 * @class : TextContentCommand
 * @brief : 文本内容命令定义
 * @note  : 回退显示旧的文字，恢复使用新的文字
 */
class TextContentCommand : public Command
{
public:
    explicit TextContentCommand(Workspace *workspace, std::shared_ptr<Text> shape,QString preContent);

    void undo();
    void redo();

private:
    std::shared_ptr<Text> m_shape;

    QString m_oldContent;   //旧的文字内容
    QString m_nowContent;   //新的文字内容  
};

#endif // TEXTCONTENTCOMMAND_H
