#ifndef ZTPREVIEW_DLG_H_
#define ZTPREVIEW_DLG_H_

#include "ui_zentaopreview.h"

#include "usrmetatype.h"

#include <QDialog>
#include <QLayout>

class ZTPreviewDlg : public QDialog {
	Q_OBJECT

public:
	ZTPreviewDlg(QWidget* parent);
	~ZTPreviewDlg() {}

signals:

private slots:

protected:
// 	virtual void paintEvent(QPaintEvent* event) override;
// 	virtual void showEvent(QShowEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void SetupUI();
	void SetupSignal();

private:
	Ui::ZTPreviewDlg ui;
}; // ZTPreviewDlg

#endif // !ZTPREVIEW_DLG_H_
