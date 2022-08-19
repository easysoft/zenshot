#ifndef ZTSETTING_DLG_H_
#define ZTSETTING_DLG_H_

#include "ui_zentaosetting.h"

#include "httprequest/zhttprequest.h"

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QListWidget>
#include <QPushButton>

class ZTSettingDlg : public QWidget {
	Q_OBJECT

public:
	ZTSettingDlg(QWidget* parent);
	~ZTSettingDlg() {}

signals:
	void AddNewItem();
	void RemoveItem();

private slots:
	void OnAddNewItem();
	void OnRemoveItem();
	void OnButtonCancel();
	void OnButtonSave();

protected:
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void showEvent(QShowEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void SetupUI();
	void SetupSignal();

	bool SaveConfig(int index, int config_index);
	void SaveDefaultConfig(int index);

	int CalcRowWidth();
	int CalcRowHeight();

	void ResetItem(int index, const char* name, const char* url, const char* usr, const char* pass);
	void ResetItemData(int index, int value);

private:
	Ui::ZTSettingDlg ui;

	QVBoxLayout m_Layout;
	QHBoxLayout m_ButtonLayout;
	QLabel m_Title;
	QListWidget m_ZTSettingList;
	QPushButton m_SaveButton, m_CancelButton;
}; // ZTSettingDlg

#endif // !ZTSETTING_DLG_H_
