/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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
    explicit MoveCommand(Workspace *workspace, std::shared_ptr<Shape> shape,QPoint offsetPoint);

    void undo();
    void redo();

private:
    std::shared_ptr<Shape> m_shape;
    QPoint m_offsetPoint;  //移动的偏移量 
};

#endif // MOVECOMMAND_H
