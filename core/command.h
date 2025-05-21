/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef COMMAND_H
#define COMMAND_H

class Workspace;

/**
 * @class : Command
 * @brief : 命令基类定义
 * @note  : 取消操作，恢复取消的操作
 */
class Command
{
public:

    explicit Command(Workspace *workspace);

    /**
     * @brief 取消操作
     */
    virtual void undo()=0;

    /**
     * @brief 恢复操作
     */
    virtual void redo()=0;

protected:
    Workspace *m_workspace;
};

#endif // COMMAND_H
