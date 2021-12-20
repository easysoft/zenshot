#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "core/command.h"
#include "core/shape.h"

/**
 * @class : AddCommand
 * @brief : 新增命令定义
 * @note  : 删除新增的图形，恢复删除的图形
 */
class AddCommand : public Command
{
public:
    /**
     * @brief AddCommand
     * @param workspace 工作空间
     * @param shape 目标图形
     */
    explicit AddCommand(Workspace *workspace,Shape *shape);

    void undo();
    void redo();

private:
    Shape *m_shape;    
};

#endif // ADDCOMMAND_H
