#include "starterui.h"

#include "starter.h"
#include "config/xmlconfig.h"
#include "spdlogwrapper.hpp"

#ifdef Q_OS_WIN
#include <Windows.h>
#endif // Q_OS_WIN
#include <QMenu>

StarterUI::StarterUI()
	: QWidget(0)
	, trayIcon(new QSystemTrayIcon(this))
	, trayIconMenu(new QMenu(this))
	, m_SettingDlg(this)
	, m_Shotting(false)
#if IS_TEST_VER
	, m_startShot(this)
#endif // IS_TEST_VER
{
	qRegisterMetaType<Starter*>("Starter*");
	qRegisterMetaType<int32_t>("int32_t");
	qRegisterMetaType<uint32_t>("uint32_t");

	createActions();
	createTrayIcon();

	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
#if !IS_TEST_VER
	setAttribute(Qt::WA_TranslucentBackground, true);
#else
	m_startShot.setText(u8"start");
	connect(&m_startShot, SIGNAL(clicked()), this, SIGNAL(SatrtShot()));
#endif // IS_TEST_VER

	connect(this, SIGNAL(SatrtShot()), this, SLOT(OnStartShot()));
// 	connect(trayIcon, &QSystemTrayIcon::activated, this, &Window::iconActivated);

	trayIcon->show();

	GetXMLConfig().LoadConfig(SETTING_XML_NAME);
	if (GetXMLConfig().GetConfigNum2("config", "enable")) 
	{
		uint32_t value = GetXMLConfig().GetConfigNum2("config", "hotkey");
		if (value)
		{
			emit CheckHotKey(value);
		}
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

	shotAction = new QAction(tr("S&hot"), this);
	QIcon shotIcon(":/images/menu-shot.png");
	shotAction->setIcon(shotIcon);
	connect(shotAction, &QAction::triggered, this, &StarterUI::OnStartShot);

	quitAction = new QAction(tr("&Quit"), this);
	QIcon quitIcon(":/images/menu-exit.png");
	quitAction->setIcon(quitIcon);
	connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void StarterUI::createTrayIcon()
{
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(settingAction);
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

void StarterUI::closeEvent(QCloseEvent*)
{
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

void StarterUI::OnShowSetting()
{
	if (!m_SettingDlg.isVisible()) 
	{
		m_SettingDlg.show();
	}
	
	m_SettingDlg.raise();
	m_SettingDlg.activateWindow();
}
