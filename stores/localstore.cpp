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
