#ifndef LOCALSTORE_H
#define LOCALSTORE_H

#include "core/store.h"

class LocalStore : public Store
{
public:
    explicit LocalStore();

    void write(const QString &group, const QString &key, const QVariant &value);
    QVariant read(const QString &group, const QString &key, const QVariant &defaultvalue);
};

#endif // LOCALSTORE_H
