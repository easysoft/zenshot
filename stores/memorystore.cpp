/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
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
