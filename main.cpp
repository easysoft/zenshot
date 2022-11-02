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
#ifdef __unix__
#include <gtk/gtk.h>
#endif // __unix__
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QMetaEnum>
#include <QFile>
#include <QList>
#include <QFontDatabase>
#include <QWidget>

#include "spdlogwrapper.hpp"

#include "widget.h"
#include "starterui.h"
#include "starter.h"
#include "core/screeninfo.h"
#include "screen/helper/screengetter.h"
#include "core/gparams.h"

#include <QDir>
#include <QLockFile>
#include <QCommandLineParser>
#include <QCommandLineOption>

#ifdef Q_OS_WIN
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif // Q_OS_WIN

#ifdef IS_XUANXUAN_VER_
static const char mutex_name[] = "zenshot.zentao.xx";
#else
static const char mutex_name[] = "zenshot.zentao";
#endif // IS_XUANXUAN_VER_

int main(int argc, char *argv[])
{
#ifdef USE_SPDLOG_
#ifdef Q_OS_WIN
    mkdir("logs");
#else
    mkdir("logs", S_IRWXU);
#endif // Q_OS_WIN
    spdlog::spdlog_init("zenshot", "logs/log.log", 23, 57, 0, 0);
    L_TRACE("start");
#endif // USE_SPDLOG_

	QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

	QApplication a(argc, argv);
    for (int i = 0; i < argc; i++)
        L_TRACE("[{0}] = {1}", i, argv[i]);

    QCoreApplication::setApplicationName("ZenShot");
    QCoreApplication::setApplicationVersion("1.2.1");

    QCommandLineOption* ops[] =
    {
        new QCommandLineOption("mark", "", "mark"),
        new QCommandLineOption("m", "", "mark"),
        new QCommandLineOption("save", "", "save"),
        new QCommandLineOption("s", "", "save"),
		new QCommandLineOption("clipboard", "", "clipboard"),
		new QCommandLineOption("c", "", "clipboard"),
    };
	QCommandLineParser parser;
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    parser.setApplicationDescription("ZenShot");
    parser.addHelpOption();
    parser.addVersionOption();

    for (int i = 0; i < sizeof(ops) / sizeof(ops[0]); i++)
        parser.addOption(*ops[i]);
	
    parser.process(a);

    std::string m, s, c;
	if (parser.isSet("m"))
		m = parser.value("m").toStdString();
    else if (parser.isSet("mark"))
        m = parser.value("mark").toStdString();
    L_TRACE("*** m = {0} & {1}", m.c_str(), m.length());

	if (parser.isSet("s"))
		s = parser.value("s").toStdString();
    else if (parser.isSet("save"))
        s = parser.value("save").toStdString();
    L_TRACE("*** s = {0} & {1}", s.c_str(), s.length());

	if (parser.isSet("c"))
		c = parser.value("c").toStdString();
    else if (parser.isSet("clipboard"))
        c = parser.value("clipboard").toStdString();
    L_TRACE("*** c = {0} & {1}", c.c_str(), c.length());

    bool is_client = true;
    QLocalSocket local_sock;
    QLocalServer local_server;
    local_sock.connectToServer(mutex_name);
    if (m.empty() && s.empty() && c.empty())
    {
        if (local_sock.waitForConnected(800))
        {
            local_sock.disconnectFromServer();
            local_sock.close();

            L_TRACE("already running ...");
            return 0;
        }

        QLocalServer::removeServer(mutex_name);
        if (!local_server.listen(mutex_name))
        {
            L_TRACE("local_server listen {0} failed ...", mutex_name);
            return 0;
        }
        is_client = false;
    }
    else 
    {
		if (!local_sock.waitForConnected(800))
		{
			local_sock.disconnectFromServer();
			local_sock.close();

            L_TRACE("connect to server {0} failed ...", mutex_name);
			return 0;
		}

        std::string pkg;
        if (!m.empty())
        {
            pkg.append("m:")
                .append(m.c_str())
                .append(";");
        }

		if (!s.empty())
		{
            pkg.append("s:")
                .append(s.c_str())
                .append(";");
		}

		if (!c.empty())
		{
            pkg.append("c:")
                .append(c.c_str())
                .append(";");
		}

        if (pkg.empty())
        {
            return 0;
        }

        int l = local_sock.write(pkg.c_str());
        L_DEBUG("## send: {0}, size: {1}", pkg.c_str(), l);

        while (local_sock.isOpen() && !local_sock.waitForReadyRead())
            std::this_thread::sleep_for(std::chrono::milliseconds(300));

		QTextStream stream(&local_sock);
		int ret = stream.readAll().toInt();
        L_DEBUG("## recv: ret - {0}", ret);
        return ret;
    }

//     QString full_name = QDir::temp().absoluteFilePath(mutex_name);
//     L_TRACE(full_name.toStdString().c_str());
//     QLockFile file(full_name);
//     if (!file.tryLock())
//     {
//         L_TRACE("already running ...");
//         return 0;
//     }

#ifdef Q_OS_UNIX
    gdk_init(NULL, NULL);
#endif // Q_OS_LINUX

#if !IS_XUANXUAN_VER_
	if (!QSystemTrayIcon::isSystemTrayAvailable()) {
		L_ERROR("system tray disabled");
		return 1;
	}
#endif // IS_XUANXUAN_VER_

    //加载并应用语言翻译界面
    QLocale locale;
    QLocale::Language langEnum = locale.language();
    QMetaEnum metaEnum = QMetaEnum::fromType<QLocale::Language>();
    const char* langChar = metaEnum.valueToKey(langEnum);
    QString langName(langChar);

    QString langFile = ":/translations/" + langName + ".qm";
    if(QFile(langFile).exists() == false)
    {
        langFile = ":/translations/English.qm";
    }

    QTranslator translator;
    translator.load(langFile);
    a.installTranslator(&translator);

    //加载图标字体文件
    int fontId = QFontDatabase::addApplicationFont(":/iconfont.ttf");
    QString fontNmae = QFontDatabase::applicationFontFamilies(fontId).at(0);

    //设置系统默认字体
    QFont defaultFont("微软雅黑",9);
    a.setFont(defaultFont);

    //解析命令行参数
    int result = GParams::instance()->fromArgs(argc,argv);

    if(result != 0)
        return result;

    a.setQuitOnLastWindowClosed(false);

    StarterUI ui(&local_server);
	ui.show();

    int ret = a.exec();
    return ret;
}
