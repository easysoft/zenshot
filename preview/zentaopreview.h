#ifndef ZTPREVIEW_DLG_H_
#define ZTPREVIEW_DLG_H_

#include "ui_zentaopreview.h"

#include "usrmetatype.h"

#include <QWidget>
#include <QLayout>
#include <QButtonGroup>
#include <QStringListModel>

class ZTPreview : public QWidget {
	Q_OBJECT
#if !NZENTAO_VER_
public:
	ZTPreview(QWidget* parent);
	~ZTPreview() {}

    std::string GetCurrentSite();

signals:
	void SubmitDemand();
	void SubmitBug();

private slots:
	void OnShowThumbnail(std::shared_ptr<QPixmap> pixmap);

protected:
// 	virtual void paintEvent(QPaintEvent* event) override;
    virtual void hideEvent(QHideEvent* event) override;
	virtual void showEvent(QShowEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void SetupUI();
	void SetupSignal();

private:
	Ui::ZTPreview ui;

	QListView* m_listView;
	QStringListModel* m_listModel;

	QButtonGroup m_BtnGroup;
	QPushButton* m_btnDemand;
	QPushButton* m_btnBug;

	QLabel* m_imgview;
#endif // NZENTAO_VER_
}; // ZTPreviewDlg

#endif // !ZTPREVIEW_DLG_H_
