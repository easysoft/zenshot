#ifndef ZTSUBMIT_DLG_H_
#define ZTSUBMIT_DLG_H_

#include "ui_zentaosubmit.h"

#include "zentaopreview.h"
#include "zentaodemand.h"

#include "usrmetatype.h"

#include <QDialog>
#include <QStackedWidget>

class ZTSubmitDlg : public QDialog {
	Q_OBJECT

public:
	ZTSubmitDlg(QWidget* parent);
	~ZTSubmitDlg() {}

signals:

private slots:

protected:
	// 	virtual void paintEvent(QPaintEvent* event) override;
	// 	virtual void showEvent(QShowEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void InitUI();
	void SetupUI();
	void SetupSignal();

private:
	Ui::ZTSubmitDlg ui;

	QStackedWidget* m_framesWidget;

	ZTPreview m_Preview;
	ZTDemand m_Demand;
}; // ZTSubmitDlg

#endif // !ZTSUBMIT_DLG_H_
