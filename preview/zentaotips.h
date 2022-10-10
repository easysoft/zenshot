#ifndef ZENTAOTIPSDLG_H
#define ZENTAOTIPSDLG_H

#include "ui_zentaotips.h"
#include "usrmetatype.h"

#include <QDialog>
#include <QTimer>

class ZTTipsDlg : public QDialog {
	Q_OBJECT
public:
	ZTTipsDlg(QWidget* parent);
	~ZTTipsDlg() {}

	void SetContent(bool success, const QString& msg);

signals:
	void OpenZentaoUrl();
	void TipsZentaoHide();

private slots:
	void OnUpdate3Sec();
	void OnBtnModify();

private:
	void InitUI();
	void SetupUI();
	void SetupSignal();

	void Update3SecTxt();

protected:
	virtual void showEvent(QShowEvent* event) override;
	virtual void hideEvent(QHideEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	Ui::ZTTipsDlg ui;

	QLabel* m_labelSuccess;
	QLabel* m_labelFailed;
	QLabel* m_labelMsg;
	QPushButton* m_btnOkay;
	QPushButton* m_btnModify;
	QPushButton* m_btn3Sec;

	QTimer m_3SecTimer;
	int m_Count;
}; // ZTTipsDlg

#endif // ZENTAOTIPSDLG_H
