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

	void ProductChanged(int index);
	void ModuleChanged(int index);
	void PriChanged(int index);
	void SeverityChanged(int index);
	void VersionChanged(int index);

private slots:
	void OnProductChanged(int index);
	void OnModuleChanged(int index);
	void OnPriChanged(int index);
	void OnSeverityChanged(int index);
	void OnVersionChanged(int index);

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
}; // ZTSubmitDlg

#endif // !ZTDBUG_DLG_H_
