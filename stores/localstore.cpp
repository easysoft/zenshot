/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "localstore.h"

#include <QSettings>
#include <QDir>

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windowsx.h>
#include <shlobj.h>
#endif // Q_OS_WIN

LocalStore::LocalStore():Store(), setting_ini()
{
#ifdef Q_OS_WIN
	char config_path[MAX_PATH] = { 0 };
	if (SHGetSpecialFolderPathA(0, config_path, CSIDL_LOCAL_APPDATA, FALSE)) {
		setting_ini = config_path;
		setting_ini.append("/ZenShot/");
		QDir dir;
		if (!dir.exists(setting_ini.c_str())) {
			dir.mkdir(setting_ini.c_str());
		}
	}
#else
	setting_ini.append("~/");
#endif // Q_OS_WIN

	setting_ini.append("setting.ini");
}

void LocalStore::write(const QString &group, const QString &key, const QVariant &value)
{
    QSettings settings(setting_ini.c_str(),QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(key,value);
}

QVariant LocalStore::read(const QString &group, const QString &key, const QVariant &defaultvalue)
{
    QVariant val;
    QString keyPos=group+"/"+key;
    QSettings settings(setting_ini.c_str(),QSettings::IniFormat);
    val=settings.value(keyPos,defaultvalue);

    return val;
}
