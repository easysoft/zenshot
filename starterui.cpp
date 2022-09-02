#include "starterui.h"

#include "starter.h"
#include "config/xmlconfig.h"
#include "spdlogwrapper.hpp"

#include "usrmetatype.h"

#include <QMenu>
#include <QDir>

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windowsx.h>
#include <shlobj.h>
#endif // Q_OS_WIN

StarterUI* g_start_ui_;
extern std::string SETTING_XML_NAME;

StarterUI::StarterUI()
	: QWidget(0)
	, trayIcon(new QSystemTrayIcon(this))
	, trayIconMenu(new QMenu(this))
	, m_SettingDlg(this)
#if !NZENTAO_VER_
	, m_ZTSettingDlg(nullptr)
	, m_ZTSubmitDlg(nullptr)
	, m_HttpReq()
#endif // NZENTAO_VER_
	, m_Shotting(false)
{
	g_start_ui_ = this;

	qRegisterMetaType<Starter*>("Starter*");
	qRegisterMetaType<int32_t>("int32_t");
	qRegisterMetaType<uint32_t>("uint32_t");
	qRegisterMetaType<string_ptr>("string_ptr");
	qRegisterMetaType<std::shared_ptr<QPixmap>>("std::shared_ptr<QPixmap>");
	qRegisterMetaType<Workspace*>("Workspace*");

	createActions();
	createTrayIcon();

	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
	setAttribute(Qt::WA_TranslucentBackground, true);

	connect(this, SIGNAL(SatrtShot()), this, SLOT(OnStartShot()));
	connect(this, SIGNAL(CheckHotKey(uint32_t)), &m_SettingDlg, SIGNAL(InitHotKeyValue(uint32_t)));
 	connect(trayIcon, &QSystemTrayIcon::activated, this, &StarterUI::OnIconActivated);
#if !NZENTAO_VER_
	connect(this, SIGNAL(Thumbnail(std::shared_ptr<QPixmap>)), &m_ZTSubmitDlg, SIGNAL(ShowThumbnail(std::shared_ptr<QPixmap>)));
#endif // NZENTAO_VER_

	trayIcon->show();

#ifdef Q_OS_WIN
	char config_path[MAX_PATH] = { 0 };
	if (SHGetSpecialFolderPathA(0, config_path, CSIDL_LOCAL_APPDATA, FALSE)) {
		SETTING_XML_NAME = config_path;
		SETTING_XML_NAME.append("/ZenShot/");
		QDir dir;
		if (!dir.exists(SETTING_XML_NAME.c_str())) {
			dir.mkdir(SETTING_XML_NAME.c_str());
		}
		SETTING_XML_NAME.append("setting.xml");
	}
#endif // Q_OS_WIN

	GetXMLConfig().LoadConfig(SETTING_XML_NAME);
	uint32_t value = GetXMLConfig().GetConfigNum2("config", "hotkey");
	if (value)
	{
		emit CheckHotKey(value);
	}

	resize(0, 0);

	hide();
}

StarterUI::~StarterUI()
{
}

void StarterUI::createActions()
{
	settingAction = new QAction(tr("S&eeting"), this);
	QIcon settingIcon(":/images/menu-setting.png");
	settingAction->setIcon(settingIcon);
	connect(settingAction, &QAction::triggered, this, &StarterUI::OnShowSetting);

#if !NZENTAO_VER_
	zentaoSettingAction = new QAction(tr("Z&enTaoSeeting"), this);
	QIcon zentaosettingIcon(":/images/menu-ztsetting.png");
	zentaoSettingAction->setIcon(zentaosettingIcon);
	connect(zentaoSettingAction, &QAction::triggered, this, &StarterUI::OnShowZenTaoSetting);
#endif // NZENTAO_VER_
	shotAction = new QAction(tr("S&hot"), this);
	QIcon shotIcon(":/images/menu-shot.png");
	shotAction->setIcon(shotIcon);
	connect(shotAction, &QAction::triggered, this, &StarterUI::OnStartShot);

	quitAction = new QAction(tr("&Quit"), this);
	QIcon quitIcon(":/images/menu-exit.png");
	quitAction->setIcon(quitIcon);
	connect(quitAction, &QAction::triggered, this, &StarterUI::OnExitShot);
}

void StarterUI::createTrayIcon()
{
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(settingAction);
#if !NZENTAO_VER_
	trayIconMenu->addAction(zentaoSettingAction);
#endif // NZENTAO_VER_
	trayIconMenu->addAction(shotAction);
	trayIconMenu->addAction(quitAction);

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);

	trayIcon->setIcon(QIcon(":/zenshot.png"));
	trayIcon->setToolTip(tr("zenshot"));
}

void StarterUI::OnStartShot()
{
	if (m_Shotting)
	{
		return;
	}

	L_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>> GAME START <<<<<<<<<<<<<<<<<<<<<<<<<<<<");
	m_Shotting = true;
	Starter* starter = nullptr;
	if (m_Starer.empty())
	{
		starter = new Starter(false);
		connect(starter, SIGNAL(ShotDone(Starter*)), this, SLOT(OnShotDone(Starter*)));
	}
	else
	{
		starter = m_Starer.back();
		m_Starer.pop_back();
	}

	starter->init();

	L_TRACE("============= m_Starer size = {0}", m_Starer.size());
}

void StarterUI::OnShotDone(Starter* starter)
{
	m_Shotting = false;
	starter->cleanup();
	m_Starer.push_back(starter);

	L_TRACE("!!!!!!!!!!!!! m_Starer size = {0}", m_Starer.size());
	L_DEBUG("@@@@@@@@@@@@@@@@@@@@@@@@ GAME END @@@@@@@@@@@@@@@@@@@@@@@@@@@@");
}

void StarterUI::OnExitShot()
{
	trayIcon->hide();
	QApplication::exit(0);
}

void StarterUI::closeEvent(QCloseEvent*)
{
	trayIcon->hide();
	QApplication::exit(0);
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
bool StarterUI::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
#else
bool StarterUI::nativeEvent(const QByteArray& eventType, void* message, long* result)
#endif
{
#ifdef Q_OS_WIN
	MSG* msg = static_cast<MSG*>(message);
	if (msg->message == WM_HOTKEY)
	{
		emit SatrtShot();
	}
#endif // Q_OS_WIN

	return QWidget::nativeEvent(eventType, message, result);
}

void StarterUI::OnIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger: /* 来自于单击激活。 */
		emit SatrtShot();
		break;
	}
}

void StarterUI::OnShowSetting()
{
	if (!m_SettingDlg.isVisible()) 
	{
		m_SettingDlg.show();
	}
	
	m_SettingDlg.raise();
	m_SettingDlg.activateWindow();
}

#if !NZENTAO_VER_
void StarterUI::OnShowZenTaoSetting()
{
	if (!m_ZTSettingDlg.isVisible())
	{
		m_ZTSettingDlg.show();
	}

	m_ZTSettingDlg.raise();
	m_ZTSettingDlg.activateWindow();
}

void StarterUI::OnShowPreview(Workspace* w)
{
	if (!m_ZTSubmitDlg.isVisible())
	{
		auto pixmap = w->result();
		m_ZTSubmitDlg.show();
		emit Thumbnail(pixmap);
	}

	m_ZTSubmitDlg.raise();
	m_ZTSubmitDlg.activateWindow();
}

void StarterUI::OnLogin(string_ptr url, string_ptr usr, string_ptr pass)
{
	std::string uri = build_uri(url->c_str(), "/tokens");
	m_HttpReq.SetUrl(uri.c_str());
}

#endif // NZENTAO_VER_