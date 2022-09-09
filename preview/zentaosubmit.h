#ifndef ZTSUBMIT_DLG_H_
#define ZTSUBMIT_DLG_H_

#include "ui_zentaosubmit.h"

#include "zentaopreview.h"
#include "zentaodemand.h"
#include "zentaobug.h"

#include "usrmetatype.h"

#include <QDialog>
#include <QStackedWidget>

class ZTSubmitDlg : public QDialog {
	Q_OBJECT
#if !NZENTAO_VER_
public:
	ZTSubmitDlg(QWidget* parent);
	~ZTSubmitDlg() {}

signals:
	void RealSubmitDemand();
	void RealSubmitBug();
	void ShowThumbnail(std::shared_ptr<QPixmap> pixmap);
    void SubmitLogin(string_ptr name);
    void SubmitReqProduct();
    void SubmitReqModules(string_ptr type);
    void DemandProductItems(zproduct_item_vec_ptr items);
    void BugProductItems(zproduct_item_vec_ptr items);
    void SubmitReqModule(uint32_t product_id, string_ptr);
    void DemandModuleItems(zmodule_item_vec_ptr items);
    void BugModuleItems(zmodule_item_vec_ptr items);
    void DemandVersionItems(zversion_item_vec_ptr items);
    void BugVersionItems(zversion_item_vec_ptr items);
    void DemandPriItems(zpri_item_vec_ptr items);
    void BugPriItems(zpri_item_vec_ptr items);
    void DemandSeverityItems(zseverity_item_vec_ptr items);
    void BugSeverityItems(zseverity_item_vec_ptr items);
    void DemandOSItems(zos_item_vec_ptr items);
    void BugOSItems(zos_item_vec_ptr items);
    void DemandBrowserItems(zbrowser_item_vec_ptr items);
    void BugBrowserItems(zbrowser_item_vec_ptr items);
    void DemandTypeItems(ztype_item_vec_ptr items);
    void BugTypeItems(ztype_item_vec_ptr items);
    void SubmitReqPri();
    void SubmitReqSeverity();
    void SubmitReqVersion(uint32_t product_id, string_ptr);
    void SubmitDemandJson(uint32_t product_id, string_ptr json);
    void SubmitBugJson(uint32_t product_id, string_ptr json);

    void UploadImage();

	void SubmitDemand();
	void SubmitBug();

    void SubmitZentaoHide();

private slots:
	void OnSubmitDemand();
	void OnSubmitBug();
    void OnBtnSumitDemand();
    void OnBtnSubmitBug();
	void OnNextStep();
	void OnCancel();

    void OnSubmitLoginResult(bool result);
    void OnSubmitProductItems(zproduct_item_vec_ptr products);
    void OnSubmitModuleItems(zmodule_item_vec_ptr modules);
    void OnSubmitVersionItems(zversion_item_vec_ptr versions);
    void OnSubmitModulesItems(zpri_item_vec_ptr pris, zseverity_item_vec_ptr serveritys, zos_item_vec_ptr oss, zbrowser_item_vec_ptr browers, ztype_item_vec_ptr types);

    void OnUploadImageDone(bool success, string_ptr url);

protected:
// 	virtual void paintEvent(QPaintEvent* event) override;
	virtual void showEvent(QShowEvent* event) override;
	virtual void hideEvent(QHideEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void InitUI();
	void SetupUI();
	void SetupSignal();

private:
	Ui::ZTSubmitDlg ui;

	QStackedWidget* m_framesWidget;

	ZTPreview* m_Preview;		// IDX_PREVIEW
	ZTDemand* m_Demand;			// IDX_DEMAND
	ZTBug* m_Bug;				// IDX_BUG

	QPushButton* m_btnNext;
	QPushButton* m_btnCancel;

	QPushButton* m_btnDemand;
	QPushButton* m_btnBug;

	int m_Index;
#endif // NZENTAO_VER_
}; // ZTSubmitDlg

#endif // !ZTSUBMIT_DLG_H_
