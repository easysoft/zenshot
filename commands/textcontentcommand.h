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
    explicit TextContentCommand(Workspace *workspace,Text *shape,QString preContent);

    void undo();
    void redo();

private:
    Text *m_shape;

    QString m_oldContent;   //旧的文字内容
    QString m_nowContent;   //新的文字内容  
};

#endif // TEXTCONTENTCOMMAND_H
