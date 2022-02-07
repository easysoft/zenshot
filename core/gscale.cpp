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

#include "gscale.h"
#include "core/gparams.h"

#include <QtMath>

GScale::GScale()
{

}

float GScale::ts(float pxValue)
{
    float s = GParams::instance()->scale();

    float v = pxValue * s;

    float minV = 1.0;

    if(v == 0.0) return 0;

    return qRound(qMax(minV,v));
}
