/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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
    explicit AddCommand(Workspace *workspace, std::shared_ptr<Shape> shape);

    void undo();
    void redo();

private:
    std::shared_ptr<Shape> m_shape;
};

#endif // ADDCOMMAND_H
