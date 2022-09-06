#ifndef ZTDEMAND_DLG_H_
#define ZTDEMAND_DLG_H_

#include "ui_zentaodemand.h"

#include "zentaopreview.h"

#include "usrmetatype.h"

#include <QWidget>
#include <QLayout>

class ZTDemand : public QWidget {
	Q_OBJECT
#if !NZENTAO_VER_
public:
	ZTDemand(QWidget* parent);
	~ZTDemand() {}

    void BuildDemandJson(string_ptr json);

signals:
	void RealSubmitDemand();
	void DemainLogin(string_ptr url, string_ptr usr, string_ptr pass);
    void ProductChanged(uint32_t product_id, string_ptr type);

private slots:
    void OnProductChanged(int index);
    void OnDemandProductItems(zproduct_item_vec_ptr products);
    void OnDemandModuleItems(zmodule_item_vec_ptr modules);
    void OnDemandVersionItems(zversion_item_vec_ptr versions);
    void OnDemandPriItems(zpri_item_vec_ptr pris);
    void OnDemandSeverityItems(zseverity_item_vec_ptr serveritys);
    void OnDemandOSItems(zos_item_vec_ptr oss);
    void OnDemandBrowserItems(zbrowser_item_vec_ptr browsers);
    void OnDemandTypeItems(ztype_item_vec_ptr types);

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
	Ui::ZTDemand ui;

	QComboBox* m_boxProduct;
	QComboBox* m_boxModule;
	QComboBox* m_boxType;
	QComboBox* m_boxPri;

    QLineEdit* m_editStory;
    QTextEdit* m_textDesc;
    QLineEdit* m_editTitle;
    QTextEdit* m_texVerify;
#endif // NZENTAO_VER_
}; // ZTSubmitDlg

#endif // !ZTDEMAND_DLG_H_
