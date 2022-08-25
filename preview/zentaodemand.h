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
	Ui::ZTDemand ui;

	QFrame* m_reviewerFrame;
}; // ZTSubmitDlg

#endif // !ZTDEMAND_DLG_H_
