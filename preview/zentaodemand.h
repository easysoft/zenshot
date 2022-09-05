#ifndef ZTDEMAND_DLG_H_
#define ZTDEMAND_DLG_H_

#include "ui_zentaodemand.h"

#include "zentaopreview.h"

#include "usrmetatype.h"

#include <QWidget>
#include <QLayout>

class ZTDemand : public QWidget {
	Q_OBJECT

public:
	ZTDemand(QWidget* parent);
	~ZTDemand() {}

signals:
	void RealSubmitDemand();
	void DemainLogin(string_ptr url, string_ptr usr, string_ptr pass);

protected:
	// 	virtual void paintEvent(QPaintEvent* event) override;
	// 	virtual void showEvent(QShowEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void InitUI();
	void SetupUI();

private:
	Ui::ZTDemand ui;

	QComboBox* m_boxProduct;
	QComboBox* m_boxModule;
	QComboBox* m_boxType;
	QComboBox* m_boxPri;
}; // ZTSubmitDlg

#endif // !ZTDEMAND_DLG_H_
