#pragma once

#define IS_TEST_VER 0

#include "starter.h"

#include "setting/settingdlg.h"

#include <QWidget>
#include <QSystemTrayIcon>
#if IS_TEST_VER
#include <QPushButton>
#endif // IS_TEST_VER

#include <list>

class StarterUI : public QWidget {
	Q_OBJECT
public:
	StarterUI();
	virtual ~StarterUI();
signals:
	void SatrtShot();
	void ShotDone(Starter* starer);
	void CheckHotKey(uint32_t value);

private slots:
	void OnStartShot();
	void OnShotDone(Starter* starer);
	void OnShowSetting();
    void OnTrayActivite(QSystemTrayIcon::ActivationReason reason);

protected:
	void closeEvent(QCloseEvent*) override;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
	virtual bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);
#else
	virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#endif

private:
	void createActions();
	void createTrayIcon();

private:
#if IS_TEST_VER
	QPushButton m_startShot;
#endif // IS_TEST_VER
	std::list<Starter*> m_Starer;

	bool m_Shotting;
	
	QAction* settingAction;
	QAction* shotAction;
	QAction* quitAction;

	QSystemTrayIcon* trayIcon;
	QMenu* trayIconMenu;
	SettingDlg m_SettingDlg;
}; // StarterUI
