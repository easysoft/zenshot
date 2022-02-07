/* Copyright (C) 2022 Nature Easy Soft Network Technology Co., LTD
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

#ifndef APPPARAMS_H
#define APPPARAMS_H

#include<QObject>

class GParams : public QObject
{
public:
    static GParams* instance();

    QString mark() const;

    QString save() const;

    float scale() const;
    void setScale(float scale);

    QString clipboard() const;
    void setClipboard(const QString &clipboard);

    int fromArgs(int argc, char *argv[]);

private:
    GParams(){};
    static GParams* m_instance;

    QString m_mark;
    QString m_save;
    QString m_clipboard;

    float m_scale;
};

#endif // APPPARAMS_H
