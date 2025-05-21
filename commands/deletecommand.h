/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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
    explicit DeleteCommand(Workspace *workspace, std::shared_ptr<Shape> shape);

    void undo();
    void redo();

private:
    std::shared_ptr<Shape> m_shape;
};

#endif // DELETECOMMAND_H
