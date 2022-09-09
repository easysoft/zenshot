#pragma once

#include "starter.h"

#include "setting/settingdlg.h"
#include "setting/zentaosetting.h"
#include "preview/zentaosubmit.h"
#include "preview/zentaotips.h"

#include "httprequest/zhttprequest.h"
#include "usrmetatype.h"

#include <QWidget>
#include <QSystemTrayIcon>

#include <list>
#include <string>

class StarterUI : public QWidget {
	Q_OBJECT
public:
	StarterUI();
	virtual ~StarterUI();

	int UsrLogin(string_ptr url, string_ptr usr, string_ptr pass, QString& err_token);

signals:
	void SatrtShot();
	void ShotDone(Starter* starer);
	void CheckHotKey(uint32_t value);
#if !NZENTAO_VER_
	void StopShot(Starter* starter);
	void Thumbnail(std::shared_ptr<QPixmap> pixmap);
	void Login(string_ptr url, string_ptr usr, string_ptr pass);
    void SubmitLoginResult(bool result);

	void ReqProduct();
    void ProductItems(zproduct_item_vec_ptr products);
	void ReqModule(uint32_t product_id, string_ptr view_type);
    void ModuleItems(zmodule_item_vec_ptr modules);
	void ReqPri();
	void ReqSeverity();
	void ReqVersion(uint32_t product_id, string_ptr type);
    void VersionItems(zversion_item_vec_ptr modules);
    void ReqModules(string_ptr type);
    void ModulesItems(zpri_item_vec_ptr pris, zseverity_item_vec_ptr serveritys, zos_item_vec_ptr oss, zbrowser_item_vec_ptr browers, ztype_item_vec_ptr types);
    void UploadImageDone(bool success, string_ptr url);
#endif

private slots:
	void OnStartShot();
	void OnShotDone(Starter* starer);
	void OnExitShot();
	void OnShowSetting();

	void OnIconActivated(QSystemTrayIcon::ActivationReason reason);
#if !NZENTAO_VER_
	void OnShowZenTaoSetting();
	void OnShowPreview(Workspace* w);
	void OnLogin(string_ptr url, string_ptr usr, string_ptr pass);
    void OnSubmitLogin(string_ptr name);
	void OnHttpProduct();
	void OnHttpModule(uint32_t product_id, string_ptr view_type);
	void OnHttpVersion(uint32_t product_id, string_ptr type);
    void OnHttpModules(string_ptr type);

    void OnSubmitDemandJson(uint32_t product_id, string_ptr json);
    void OnSubmitBugJson(uint32_t product_id, string_ptr json);

    void OnUploadImage();

	void OnOpenZentaoUrl();

	void OnTipZentaoHide();
	void OnSubmitZentaoHide();
#endif // NZENTAO_VER_

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

#if !NZENTAO_VER_
	bool IsSameUsr(const std::string& usr, const std::string& url)
	{
		return m_CurrentUsr == usr && m_CurrentUrl == url;
	}
#endif // NZENTAO_VER_

	void SetupSignal();

private:
	std::list<Starter*> m_Starer;

	bool m_Shotting;
	
	QAction* settingAction;
#if !NZENTAO_VER_
	QAction* zentaoSettingAction;

	ZTSettingDlg m_ZTSettingDlg;
	ZTSubmitDlg m_ZTSubmitDlg;
	ZTTipsDlg m_ZTTipsDlg;

	ZHttpRequest m_HttpReq;

	std::string m_CurrentUsr;
	std::string m_CurrentUrl;
	std::string m_LastSubmitUrl;

    std::shared_ptr<QPixmap> m_CurrentShot;
	Starter* m_CurrentStarter;
#endif // NZENTAO_VER_
	QAction* shotAction;
	QAction* quitAction;

	QSystemTrayIcon* trayIcon;
	QMenu* trayIconMenu;
	SettingDlg m_SettingDlg;
}; // StarterUI

extern StarterUI* g_start_ui_;
