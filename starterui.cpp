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
#ifdef Q_OS_UNIX
#include "xrecord/event_monitor.h"
#include <X11/Xlibint.h>
#endif // Q_OS_UNIX

#include <QApplication>
#include <QDesktopWidget>

StarterUI* g_start_ui_;
extern std::string SETTING_XML_NAME;

StarterUI::StarterUI()
	: QDialog(0)
	, trayIcon(new QSystemTrayIcon(this))
	, trayIconMenu(new QMenu(this))
	, m_SettingDlg(this)
#if !NZENTAO_VER_
	, m_ZTSettingDlg(this)
	, m_ZTSubmitDlg(this)
	, m_ZTTipsDlg(this)
	, m_HttpReq()
    , m_CurrentShot(nullptr)
	, m_CurrentStarter(nullptr)
	, m_CurrentUsr()
	, m_CurrentUrl()
	, m_LastSubmitUrl()
#endif // NZENTAO_VER_
#ifdef Q_OS_UNIX
	, m_EventMonitor(new EventMonitor(this))
	, m_PrevClkTick(0)
#endif // Q_OS_UNIX
	, m_Shotting(false)
{
	g_start_ui_ = this;

	qRegisterMetaType<Starter*>("Starter*");
	qRegisterMetaType<int32_t>("int32_t");
	qRegisterMetaType<uint32_t>("uint32_t");
	qRegisterMetaType<string_ptr>("string_ptr");
	qRegisterMetaType<Workspace*>("Workspace*");
#if !NZENTAO_VER_
    qRegisterMetaType<std::shared_ptr<QPixmap>>("std::shared_ptr<QPixmap>");
    qRegisterMetaType<zproduct_item_vec_ptr>("zproduct_item_vec_ptr");
    qRegisterMetaType<zmodule_item_vec_ptr>("zmodule_item_vec_ptr");
    qRegisterMetaType<zversion_item_vec_ptr>("zversion_item_vec_ptr");
    qRegisterMetaType<ztype_item_vec_ptr>("ztype_item_vec_ptr");
    qRegisterMetaType<zos_item_vec_ptr>("zos_item_vec_ptr");
    qRegisterMetaType<zbrowser_item_vec_ptr>("zbrowser_item_vec_ptr");
    qRegisterMetaType<zseverity_item_vec_ptr>("zseverity_item_vec_ptr");
    qRegisterMetaType<zpri_item_vec_ptr>("zpri_item_vec_ptr");
#endif // NZENTAO_VER_
#ifdef Q_OS_UNIX
	memset(m_PressedKey, 0, sizeof(m_PressedKey));
#endif // Q_OS_UNIX

	createActions();
	createTrayIcon();

	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
	setAttribute(Qt::WA_TranslucentBackground, true);
	
	SetupSignal();

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

#ifdef Q_OS_UNIX
	m_EventMonitor->start();
#endif // Q_OS_UNIX
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
	trayIconMenu->addAction(shotAction);
	trayIconMenu->addAction(settingAction);
#if !NZENTAO_VER_
	trayIconMenu->addAction(zentaoSettingAction);
#endif // NZENTAO_VER_
	trayIconMenu->addAction(quitAction);

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);

	trayIcon->setIcon(QIcon(":/zenshot.png"));
	trayIcon->setToolTip(tr("zenshot"));
}

#ifdef Q_OS_UNIX
bool StarterUI::CheckHotKeyTrigger()
{
	return false;
}
#endif // Q_OS_UNIX

void StarterUI::SetupSignal()
{
	connect(this, SIGNAL(SatrtShot()), this, SLOT(OnStartShot()));
	connect(this, SIGNAL(CheckHotKey(uint32_t)), &m_SettingDlg, SIGNAL(InitHotKeyValue(uint32_t)));
	connect(trayIcon, &QSystemTrayIcon::activated, this, &StarterUI::OnIconActivated);
#if !NZENTAO_VER_
	connect(this, SIGNAL(Thumbnail(std::shared_ptr<QPixmap>)), &m_ZTSubmitDlg, SIGNAL(ShowThumbnail(std::shared_ptr<QPixmap>)));
	connect(this, SIGNAL(Login(string_ptr, string_ptr, string_ptr)), this, SLOT(OnLogin(string_ptr, string_ptr, string_ptr)));
    connect(&m_ZTSubmitDlg, SIGNAL(SubmitLogin(string_ptr)), this, SLOT(OnSubmitLogin(string_ptr)));
    connect(this, SIGNAL(SubmitLoginResult(bool)), &m_ZTSubmitDlg, SLOT(OnSubmitLoginResult(bool)));

    connect(&m_ZTSubmitDlg, SIGNAL(SubmitReqProduct()), this, SIGNAL(ReqProduct()));
    connect(this, SIGNAL(ReqProduct()), this, SLOT(OnHttpProduct()));
    connect(this, SIGNAL(ProductItems(zproduct_item_vec_ptr)), &m_ZTSubmitDlg, SLOT(OnSubmitProductItems(zproduct_item_vec_ptr)));

    connect(&m_ZTSubmitDlg, SIGNAL(SubmitReqModule(uint32_t, string_ptr)), this, SIGNAL(ReqModule(uint32_t, string_ptr)));
    connect(this, SIGNAL(ReqModule(uint32_t, string_ptr)), this, SLOT(OnHttpModule(uint32_t, string_ptr)));
    connect(this, SIGNAL(ModuleItems(zmodule_item_vec_ptr)), &m_ZTSubmitDlg, SLOT(OnSubmitModuleItems(zmodule_item_vec_ptr)));

    connect(&m_ZTSubmitDlg, SIGNAL(SubmitReqVersion(uint32_t, string_ptr)), this, SIGNAL(ReqVersion(uint32_t, string_ptr)));
    connect(this, SIGNAL(ReqVersion(uint32_t, string_ptr)), this, SLOT(OnHttpVersion(uint32_t, string_ptr)));
    connect(this, SIGNAL(VersionItems(zversion_item_vec_ptr)), &m_ZTSubmitDlg, SLOT(OnSubmitVersionItems(zversion_item_vec_ptr)));

    connect(&m_ZTSubmitDlg, SIGNAL(SubmitReqModules(string_ptr)), this, SIGNAL(ReqModules(string_ptr)));
    connect(this, SIGNAL(ReqModules(string_ptr)), this, SLOT(OnHttpModules(string_ptr)));
    connect(this, SIGNAL(ModulesItems(zpri_item_vec_ptr, zseverity_item_vec_ptr, zos_item_vec_ptr, zbrowser_item_vec_ptr, ztype_item_vec_ptr)), &m_ZTSubmitDlg, SLOT(OnSubmitModulesItems(zpri_item_vec_ptr, zseverity_item_vec_ptr, zos_item_vec_ptr, zbrowser_item_vec_ptr, ztype_item_vec_ptr)));

    connect(&m_ZTSubmitDlg, SIGNAL(SubmitDemandJson(uint32_t, string_ptr)), this, SLOT(OnSubmitDemandJson(uint32_t, string_ptr)));
    connect(&m_ZTSubmitDlg, SIGNAL(SubmitBugJson(uint32_t, string_ptr)), this, SLOT(OnSubmitBugJson(uint32_t, string_ptr)));

    connect(&m_ZTSubmitDlg, SIGNAL(UploadImage()), this, SLOT(OnUploadImage()));
    connect(this, SIGNAL(UploadImageDone(bool, string_ptr)), &m_ZTSubmitDlg, SLOT(OnUploadImageDone(bool, string_ptr)));
	connect(&m_ZTTipsDlg, SIGNAL(OpenZentaoUrl()), this, SLOT(OnOpenZentaoUrl()));

	connect(&m_ZTSettingDlg, SIGNAL(SettingZentaoHide()), this, SLOT(OnSubmitZentaoHide()));
	connect(&m_ZTTipsDlg, SIGNAL(TipsZentaoHide()), this, SLOT(OnTipZentaoHide()));
	connect(&m_ZTSubmitDlg, SIGNAL(SubmitZentaoHide()), this, SLOT(OnSubmitZentaoHide()));
#endif // NZENTAO_VER_
#ifdef Q_OS_UNIX
	connect(m_EventMonitor, SIGNAL(buttonPress(int, int)), this, SLOT(OnEventMonitorbuttonPress(int, int)), Qt::QueuedConnection);
	connect(m_EventMonitor, SIGNAL(buttonDrag(int, int)), this, SLOT(OnEventMonitorbuttonDrag(int, int)), Qt::QueuedConnection);
	connect(m_EventMonitor, SIGNAL(buttonRelease(int, int)), this, SLOT(OnEventMonitorbuttonRelease(int, int)), Qt::QueuedConnection);
	connect(m_EventMonitor, SIGNAL(keyPress(int)), this, SLOT(OnEventMonitorkeyPress(int)), Qt::QueuedConnection);
	connect(m_EventMonitor, SIGNAL(keyRelease(int)), this, SLOT(OnEventMonitorkeyRelease(int)), Qt::QueuedConnection);
#endif // Q_OS_UNIX
}

void StarterUI::CenterDlg(QWidget* widget)
{
	int w = QApplication::desktop()->screen(0)->width(),
		h = QApplication::desktop()->screen(0)->height();

	int w1 = widget->width(),
		h1 = widget->height();

	widget->move((w - w1) / 2, (h - h1) / 2);
}

void StarterUI::OnStartShot()
{
	if (m_Shotting)
	{
		return;
	}

	L_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>> GAME START <<<<<<<<<<<<<<<<<<<<<<<<<<<<");
#ifdef Q_OS_UNIX
	memset(m_PressedKey, 0, sizeof(m_PressedKey));
	m_PrevClkTick = 0;
#endif // Q_OS_UNIX

	m_Shotting = true;
	Starter* starter = nullptr;
	if (m_Starer.empty())
	{
		starter = new Starter(false);
		connect(this, SIGNAL(StopShot(Starter*)), starter, SIGNAL(ShotDone(Starter*)));
		connect(starter, SIGNAL(ShotDone(Starter*)), this, SLOT(OnShotDone(Starter*)));
	}
	else
	{
		starter = m_Starer.back();
		m_Starer.pop_back();
	}

#if !NZENTAO_VER_
	m_CurrentStarter = starter;
#endif // NZENTAO_VER_
	starter->init();

	L_TRACE("============= m_Starer size = {0}", m_Starer.size());
}

void StarterUI::OnShotDone(Starter* starter)
{
#if !NZENTAO_VER_
    m_CurrentShot = nullptr;
	m_CurrentStarter = nullptr;
#endif // NZENTAO_VER_
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

#ifdef Q_OS_UNIX
void StarterUI::OnEventMonitorbuttonPress(int x, int y)
{
	bool is_dbclk = false;
	if (time(0) - m_PrevClkTick < 1)
	{
		is_dbclk = true;
		m_PrevClkTick = 0;
	}
	else
	{
		m_PrevClkTick = time(0);
	}

	if (is_dbclk)
	{
		L_TRACE("{0} - DBCLK", __FUNCTION__);
	}
	else
	{
		L_TRACE("{0} - NO {1}", __FUNCTION__, m_PrevClkTick);
	}
}

void StarterUI::OnEventMonitorbuttonDrag(int x, int y)
{
}


void StarterUI::OnEventMonitorbuttonRelease(int x, int y)
{
}

void StarterUI::OnEventMonitorkeyPress(int code)
{
	if (!m_PressedKey[code])
	{
		CheckHotKeyTrigger();
	}
	m_PressedKey[code] = time(0);

	L_TRACE("+++++++++++++ key -> {0} pressed", code);
}

void StarterUI::OnEventMonitorkeyRelease(int code)
{
	m_PressedKey[code] = 0;
	L_TRACE("------------- key -> {0} released", code);
}
#endif // Q_OS_UNIX

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

	return QDialog::nativeEvent(eventType, message, result);
}

void StarterUI::OnIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger: /* �����ڵ������ */
		emit SatrtShot();
		break;
	}
}

void StarterUI::OnShowSetting()
{
	if (!m_SettingDlg.isVisible()) 
	{
		m_SettingDlg.showNormal();
		CenterDlg(&m_SettingDlg);
	}
	
	m_SettingDlg.raise();
	m_SettingDlg.activateWindow();
}
