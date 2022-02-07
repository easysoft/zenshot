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

#include "memorystore.h"

MemoryStore::MemoryStore():Store()
{

}

void MemoryStore::write(const QString &group, const QString &key, const QVariant &value)
{
    QString keyPos=group+"/"+key;
    m_map[keyPos] = value;
}

QVariant MemoryStore::read(const QString &group, const QString &key, const QVariant &defaultvalue)
{
    QString keyPos=group+"/"+key;

    if(m_map.contains(keyPos) == false)
    {
        return defaultvalue;
    }

    return  m_map[keyPos];
}
