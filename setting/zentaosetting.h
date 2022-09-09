#ifndef ZTSETTING_DLG_H_
#define ZTSETTING_DLG_H_

#include "ui_zentaosetting.h"

#include "ztsettingdetail.h"
#include "ztsettinglist.h"
#include "ztsettinglistitem.h"

#include "usrmetatype.h"

#include <QDialog>
#include <QLayout>

class ZTSettingDlg : public QDialog {
	Q_OBJECT
#if !NZENTAO_VER_
public:
	ZTSettingDlg(QWidget* parent);
	~ZTSettingDlg() {}

signals:
	void AddNewItem();
	void RemoveItem();
	void ConfigCancel();
	void CheckConfig();
	void SaveZentaoSiteConfig();
	void SaveZentaoDefaultSite();
	void SaveZentaoCurrentSite(string_ptr name, string_ptr url, string_ptr usr, string_ptr pass);
	void RealRemoveItem(ZTSettingListItem* item);
	void SettingZentaoHide();

private slots:
	void OnConfigCancel();
	void OnConfigSave();
	void OnCheckInputDone();

protected:
// 	virtual void paintEvent(QPaintEvent* event) override;
// 	virtual void showEvent(QShowEvent* event) override;
	virtual void hideEvent(QHideEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void SetupUI();
	void SetupSignal();

private:
	Ui::ZTSettingDlg ui;

	QHBoxLayout m_Layout;
	ZTSettingDetail m_Detail;
	ZTSettingList m_List;
#endif // NZENTAO_VER_
}; // ZTSettingDlg

#endif // !ZTSETTING_DLG_H_
