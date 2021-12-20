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
