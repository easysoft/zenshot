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

#ifndef AREALOCATOR_H
#define AREALOCATOR_H

#include "core/locator.h"
#include "core/utils.h"

class ShotArea;

class AreaLocator : public Locator
{
public:
    AreaLocator(ShotArea* shape,Utils::RectAnchor anchor);

    Utils::RectAnchor anchor() const;
    void setAnchor(const Utils::RectAnchor &anchor);

    QPoint location();
    void setLocation(QPoint point);

private:
    Utils::RectAnchor m_anchor;
    ShotArea* m_shotArea;
};

#endif // AREALOCATOR_H
