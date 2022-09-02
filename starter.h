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

#ifndef APPINSTALL_H
#define APPINSTALL_H

#include <QObject>

#include "widget.h"

class Starter
    : public QObject
{
    Q_OBJECT
public:
    Starter(bool exit_process);
    virtual ~Starter();

    void init(QWidget* parent = nullptr);
    void cleanup();
    std::shared_ptr<QPixmap> result();

private:
    QList<Widget*>* m_widgets;
    QList<Widget*>* m_unused_widgets;

signals:
    void ShotDone(Starter*);
    void ShotResult(std::shared_ptr<QPixmap> pixmap);

private slots:
    void finishShot(int code);
    void finishConfirmArea();

private:
    bool m_bExit;
};

#endif // APPINSTALL_H
