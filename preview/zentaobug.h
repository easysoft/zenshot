#ifndef ZTDBUG_DLG_H_
#define ZTDBUG_DLG_H_

#include "ui_zentaobug.h"

#include "zentaopreview.h"
#include "usrmetatype.h"

#include <QWidget>
#include <QLayout>

class ZTBug : public QWidget {
	Q_OBJECT
#if !NZENTAO_VER_
public:
	ZTBug(QWidget* parent);
	~ZTBug() {}


signals:
	void RealSubmitBug();

	void ProductChanged(uint32_t id, string_ptr view_type);
	void ModuleChanged(uint32_t id);
	void PriChanged(uint32_t id);
	void SeverityChanged(uint32_t id);
	void VersionChanged(uint32_t id);

private slots:
    void OnBugProductItems(zproduct_item_vec_ptr products);
    void OnBugModuleItems(zmodule_item_vec_ptr modules);
    void OnBugVersionItems(zversion_item_vec_ptr versions);
    void OnBugPriItems(zpri_item_vec_ptr pris);
    void OnBugSeverityItems(zseverity_item_vec_ptr serveritys);
    void OnBugOSItems(zos_item_vec_ptr oss);
    void OnBugBrowserItems(zbrowser_item_vec_ptr browsers);
    void OnBugTypeItems(ztype_item_vec_ptr types);
	void OnProductChanged(int index);

protected:
	// 	virtual void paintEvent(QPaintEvent* event) override;
	// 	virtual void showEvent(QShowEvent* event) override;
    virtual void hideEvent(QHideEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void InitUI();
	void SetupUI();
	void SetupSignal();

private:
	Ui::ZTBug ui;

	QComboBox* m_boxProduct;
	QComboBox* m_boxModule;
	QComboBox* m_cbxPri;
	QComboBox* m_cbxSeverity;
	QComboBox* m_boxVersion;
	QComboBox* m_cbxBrower;
	QComboBox* m_cbxOS;
	QComboBox* m_cbxType;

	QLineEdit* m_editTitle;
	QTextEdit* m_textDesc;
	QDateEdit* m_TimeEditDeadLine;
#endif //NZENTAO_VER_
}; // ZTSubmitDlg

#endif // !ZTDBUG_DLG_H_
