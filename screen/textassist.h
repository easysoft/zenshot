/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef TEXTASSIST_H
#define TEXTASSIST_H

#include <QPoint>

#include "controls/textwidget.h"
#include "shapes/text.h"

class Workspace;

/**
 * @class : TextAssist
 * @brief : 文本编辑辅助类定义
 * @note  : 提供文本的在位输入，修改功能
 */
class TextAssist
{
public:
    explicit TextAssist(Workspace *m_workspace);

    /**
     * @brief 获取是否正在编辑
     * @return
     */
    bool editing() const;

    /**
     * @brief 关联文本图形对象并启动编辑
     * @param m_shape
     */
    void attach(std::shared_ptr<Text> m_shape);

    /**
     * @brief 接触关联，并结束文本编辑
     */
    void unAttach();

    /**
     * @brief 更新属性
     */
    void refreshProps();

    void cleanup();

private:
    bool m_editing;                 //是否正在编辑标识
    std::shared_ptr<Text> m_shape;  //关联的文本对象
    QString m_preContent;           //文本图形之前的内容

    TextWidget *m_textWidget;       //文本编辑组件对象
    Workspace *m_workspace;         //工作空间
};

#endif // TEXTASSIST_H
