#ifndef ZTSETTING_ITEM_H_
#define ZTSETTING_ITEM_H_

#include "ui_zentaosettingdetail.h"

#include "usrmetatype.h"

#include <QWidget>
#include <QLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>

class ZTSettingDetail : public QWidget {
	Q_OBJECT
#if !NZENTAO_VER_
public:
	ZTSettingDetail(QWidget* parent);
	~ZTSettingDetail() {}

	std::string GetName() { return m_textName->text().toUtf8().toStdString(); }
	std::string GetUrl() { return m_textUri->text().toUtf8().toStdString(); }
	std::string GetUsr() { return m_textUsr->text().toUtf8().toStdString(); }
	std::string GetPass() { return m_textPass->text().toUtf8().toStdString(); }

	void SetName(const char* name) { m_textName->setText(name); }
	void SetUrl(const char* url) { m_textUri->setText(url); }
	void SetUsr(const char* usr) { m_textUsr->setText(usr); }
	void SetPass(const char* pass) { m_textPass->setText(pass); }

	void Clear()
	{
		SetName("");
		SetUrl("");
		SetUsr("");
		SetPass("");
	}

	void SetDefaultSiteName(const std::string& name);

	virtual bool eventFilter(QObject* watched, QEvent* event) override;
// 
// 	void SetUserData(int value) 
// 	{ 
// 		m_NewItemButton.setUserData(ITEM_INDEX_DATA, reinterpret_cast<QObjectUserData*>(value)); 
// 		m_RemoveItemButton.setUserData(ITEM_INDEX_DATA, reinterpret_cast<QObjectUserData*>(value)); 
// 	}
// 	
// 	virtual bool eventFilter(QObject* watched, QEvent* event) override;

signals:
	void CheckInputDone();
	void ChangeCurrentSelectDetail(int index, string_ptr name, string_ptr url, string_ptr usr, string_ptr pass);
	void SaveDefaultSite();
	void ConfigSave();
	void ConfigNew();
    void SetDefaultSite(bool flag);

	void UpdateName(const QString& name);
	void UpdateUrl(const QString& url);
	void UpdateUsr(const QString& usr);
	void UpdatePass(const QString& pass);

private slots:
	void OnChangeCurrentSelectDetail(int index, string_ptr name, string_ptr url, string_ptr usr, string_ptr pass);
	void OnStateChanged(int state);
	void OnSaveDefaultSite();
	void OnSetDefaultSiteName(string_ptr name);

protected:
	virtual void showEvent(QShowEvent* event) override;

private:
	void InitUI();
	void SetupUI();
	void SetupSignal();

private:
	Ui::zentaosettingdetail ui;

	QCheckBox* m_checkSetDefault;
	
	QLabel* m_labelNameTitle;
	QLabel* m_labelUriTitle;
	QLabel* m_labelUsr;
	QLabel* m_labelPass;
	
	QPushButton* m_btnSave;
	QPushButton* m_btnNew;

	QLineEdit* m_textName;
	QLineEdit* m_textUri;
	QLineEdit* m_textUsr;
	QLineEdit* m_textPass;
	
	std::string m_DefaultSite;
#endif // NZENTAO_VER_
}; // ZTSettingDetail

#endif // ZTSETTING_ITEM_H_
