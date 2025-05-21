/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef PROPSCOMMAND_H
#define PROPSCOMMAND_H

#include "core/shape.h"
#include "core/command.h"
#include "core/store.h"
#include "stores/memorystore.h"

/**
 * @class : PropsCommand
 * @brief : 属性命令定义
 * @note  : 回退使用旧的属性，恢复使用新的属性
 */
class PropsCommand : public Command
{
public:
    explicit PropsCommand(Workspace *workspace,Shape *shape,MemoryStore oldStore,MemoryStore nowStore);

    void undo();
    void redo();

private:
    Shape *m_shape;
    MemoryStore m_oldStore;   //旧属性存储位置对象
    MemoryStore m_nowStore;   //新属性存储位置对象
};

#endif // PROPSCOMMAND_H
