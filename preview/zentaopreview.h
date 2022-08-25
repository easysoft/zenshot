#ifndef ZTPREVIEW_DLG_H_
#define ZTPREVIEW_DLG_H_

#include "ui_zentaopreview.h"

#include "usrmetatype.h"

#include <QWidget>
#include <QLayout>

class ZTPreview : public QWidget {
	Q_OBJECT

public:
	ZTPreview(QWidget* parent);
	~ZTPreview() {}

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
	Ui::ZTPreview ui;
}; // ZTPreviewDlg

#endif // !ZTPREVIEW_DLG_H_
