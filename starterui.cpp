#include "StarterUI.h"

#include "starter.h"
#include "setting/settingdlg.h"
#include "config/xmlconfig.h"
#include "spdlogwrapper.hpp"

#ifdef _WINDOWS
#include <Windows.h>
#endif // _WINDOWS

StarterUI::StarterUI()
	: QWidget(0)
#if IS_TEST_VER
	, m_startShot(this)
#endif // IS_TEST_VER
{
	qRegisterMetaType<Starter*>("Starter*");

	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
#if !IS_TEST_VER
	setAttribute(Qt::WA_TranslucentBackground, true);
#else
	m_startShot.setText(u8"start");
	connect(&m_startShot, SIGNAL(clicked()), this, SIGNAL(SatrtShot()));
#endif // IS_TEST_VER

	connect(this, SIGNAL(SatrtShot()), this, SLOT(OnStartShot()));
}

StarterUI::~StarterUI()
{
}

void StarterUI::OnStartShot()
{
	//SettingDlg dlg(this);
	//dlg.exec();

	Starter* starter = nullptr;
	if (m_Starer.empty()) 
	{
		starter = new Starter;
		connect(starter, SIGNAL(ShotDone(Starter*)), this, SLOT(OnShotDone(Starter*)));
	}
	else 
	{
		starter = m_Starer.back();
		m_Starer.pop_back();
	}

	starter->init();
}

void StarterUI::OnShotDone(Starter* starter)
{
	m_Starer.push_back(starter);
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
bool StarterUI::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
#else
bool StarterUI::nativeEvent(const QByteArray& eventType, void* message, long* result)
#endif
{
#ifdef Q_OS_WIN32
	if (!GetXMLConfig().GetConfigNum2("config", "enable")) 
	{
		return QWidget::nativeEvent(eventType, message, result);
	}

	MSG* msg = static_cast<MSG*>(message);
	if (msg->message == WM_HOTKEY) 
	{
		emit SatrtShot();
	}
#endif // _WINDOWS

	return QWidget::nativeEvent(eventType, message, result);
}
