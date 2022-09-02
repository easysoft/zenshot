#ifndef ZTDBUG_DLG_H_
#define ZTDBUG_DLG_H_

#include "ui_zentaobug.h"

#include "zentaopreview.h"

#include "usrmetatype.h"

#include <QWidget>
#include <QLayout>

class ZTBug : public QWidget {
	Q_OBJECT

public:
	ZTBug(QWidget* parent);
	~ZTBug() {}

signals:
	void RealSubmitBug();

protected:
	// 	virtual void paintEvent(QPaintEvent* event) override;
	// 	virtual void showEvent(QShowEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void InitUI();
	void SetupUI();
	void SetupSignal();

private:
	Ui::ZTBug ui;
}; // ZTSubmitDlg

#endif // !ZTDBUG_DLG_H_
