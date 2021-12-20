#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "core/command.h"
#include "core/shape.h"

/**
 * @class : DeleteCommand
 * @brief : 删除命令类定义
 * @note  : 添加删除的图形，删除恢复的图形
 */
class DeleteCommand : public Command
{
public:
    explicit DeleteCommand(Workspace *workspace,Shape *shape);

    void undo();
    void redo();

private:
    Shape *m_shape;  
};

#endif // DELETECOMMAND_H
