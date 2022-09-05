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

private slots:
	void OnAddNewItem();
	void OnRemoveItem();
	void OnConfigCancel();
	void OnConfigSave();
	void OnConfigNew();
	void OnCheckConfig();

protected:
// 	virtual void paintEvent(QPaintEvent* event) override;
// 	virtual void showEvent(QShowEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void SetupUI();
	void SetupSignal();

	int CalcRowWidth();
	int CalcRowHeight();

	void ResetItem(int index, const char* name, const char* url, const char* usr, const char* pass);
	void ResetItemData(int index, int value);

private:
	Ui::ZTSettingDlg ui;

	QHBoxLayout m_Layout;
	ZTSettingDetail m_Detail;
	ZTSettingList m_List;
}; // ZTSettingDlg

#endif // !ZTSETTING_DLG_H_
