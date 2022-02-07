/* Copyright (C) 2021 Nature Easy Soft Network Technology Co., LTD
 *
 * This file is part of Zenshot (https://github.com/easysoft/zenshot/).
 *
 * Zenshot is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zenshot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zenshot. If not, see <https://www.gnu.org/licenses/>.
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
