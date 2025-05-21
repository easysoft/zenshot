/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef PENCOMBOBOX_H
#define PENCOMBOBOX_H

#include <QPushButton>
#include <QVector>
#include <QMenu>

#include "controls/penrenderer.h"
#include "controls/penitemwidget.h"
#include "core/gscale.h"

/**
 * @class : PenCombobox
 * @brief : 线条样式下拉列表选择
 * @note  : 线条样式下拉列表选择
 */
class PenCombobox : public QPushButton,GScale
{
    Q_OBJECT
public:
    PenCombobox(QWidget *parent = nullptr);
    ~PenCombobox();

    Qt::PenStyle penStyle() const;
    void setPenStyle(const Qt::PenStyle &penStyle);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Qt::PenStyle m_penStyle;
    QVector<Qt::PenStyle> m_styleList;
    QVector<PenItemWidget*> m_itemWidgetList;
    PenRenderer *m_renderer;

    QMenu *m_menu;

    void createSelect();

signals:
    void penStyleChanged();

private slots:
    void menuAboutToShow();
    void menuTriggered(QAction*);
};

#endif // PENCOMBOBOX_H
