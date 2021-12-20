#ifndef MEMORYSTORE_H
#define MEMORYSTORE_H

#include "core/store.h"

#include <QMap>
#include <QVariant>

class MemoryStore : public Store
{
public:
    explicit MemoryStore();

    void write(const QString &group, const QString &key, const QVariant &value);
    QVariant read(const QString &group, const QString &key, const QVariant &defaultvalue);

private:
    QMap<QString,QVariant> m_map;
};

#endif // MEMORYSTORE_H
