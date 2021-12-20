#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "core/command.h"
#include "core/shape.h"

#include <QPoint>

/**
 * @class : MoveCommand
 * @brief : 移动命令定义
 * @note  : 回退到旧的位置，重新恢复到新的位置
 */
class MoveCommand : public Command
{
public:
    explicit MoveCommand(Workspace *workspace,Shape *shape,QPoint offsetPoint);

    void undo();
    void redo();

private:
    Shape *m_shape;
    QPoint m_offsetPoint;  //移动的偏移量 
};

#endif // MOVECOMMAND_H
