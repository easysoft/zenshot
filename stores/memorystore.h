/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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
