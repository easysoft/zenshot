/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef TEXTBAR_H
#define TEXTBAR_H

#include "core/propsbar.h"
#include "controls/sizewidget.h"
#include "controls/colorwidget.h"

#include <QComboBox>
#include <QFontComboBox>
#include <QCheckBox>

/**
 * @class : TextBar
 * @brief : 文本属性面板定义
 * @note  : 文本铅笔属性设置
 */
class TextBar : public PropsBar
{
    Q_OBJECT
public:
    explicit TextBar(Workspace *m_workspace);

private:
    QComboBox *m_fontComboxBox;        //字体组件对象
    QComboBox *m_sizeComboBox;         //字号组件对象
    ColorWidget *m_colorWidget;        //颜色组件对象
    QCheckBox *m_boldCheckBox;         //粗体组件对象
    QCheckBox *m_italicCheckBox;       //斜体组件对象
    QCheckBox *m_underlineCheckBox;    //下划线组件对象


protected:
    void createWidget();
    void loadProps();
    void saveProps();
    void connectEvents();

private slots:
    void indexChanged(int index);

};

#endif // TEXTBAR_H
