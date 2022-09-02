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

public:
	ZTSubmitDlg(QWidget* parent);
	~ZTSubmitDlg() {}

signals:
	void RealSubmitDemand();
	void RealSubmitBug();
	void ShowThumbnail(std::shared_ptr<QPixmap> pixmap);

private slots:
	void OnSubmitDemand();
	void OnSubmitBug();
	void OnNextStep();
	void OnCancel();

	void OnRealSubmitDemand();
	void OnRealSubmitBug();

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

	int m_Index;
}; // ZTSubmitDlg

#endif // !ZTSUBMIT_DLG_H_
