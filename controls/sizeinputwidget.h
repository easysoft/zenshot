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

#ifndef SIZEINPUTWIDGET_H
#define SIZEINPUTWIDGET_H

#include <QWidget>
#include <QSpinBox>

#include "core/gscale.h"

class SizeInputWidget : public QWidget,GScale
{
    Q_OBJECT
public:
    SizeInputWidget(QWidget *parent=nullptr);

    int value() const;
    void setValue(int value);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int m_minSize;
    int m_maxSize;

    QSpinBox *m_inpputBox;

signals:
    void sizeChanged();

private slots:
    void onInpputIntChanged(int);
};

#endif // SIZEINPUTWIDGET_H
