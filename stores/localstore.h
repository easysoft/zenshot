/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef LOCALSTORE_H
#define LOCALSTORE_H

#include "core/store.h"

class LocalStore : public Store
{
public:
    explicit LocalStore();

    void write(const QString &group, const QString &key, const QVariant &value);
    QVariant read(const QString &group, const QString &key, const QVariant &defaultvalue);

private:
    std::string setting_ini;
};

#endif // LOCALSTORE_H
