#ifndef ZTSETTING_ITEM_H_
#define ZTSETTING_ITEM_H_

#include "httprequest/zhttprequest.h"

#include <QWidget>
#include <QLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>

#define ITEM_INDEX_DATA 0x101

class ZTSettingItem : public QWidget {
	Q_OBJECT

public:
	ZTSettingItem(QWidget* parent);
	~ZTSettingItem() {}

	std::string GetName() { return m_Name.text().toUtf8().toStdString(); }
	std::string GetUrl() { return m_Url.text().toUtf8().toStdString(); }
	std::string GetUsr() { return m_Usr.text().toUtf8().toStdString(); }
	std::string GetPass() { return m_Pass.text().toUtf8().toStdString(); }

	void SetName(const char* name) { m_Name.setText(name); }
	void SetUrl(const char* url) { m_Url.setText(url); }
	void SetUsr(const char* usr) { m_Usr.setText(usr); }
	void SetPass(const char* pass) { m_Pass.setText(pass); }

	void Clear()
	{
		SetName("");
		SetUrl("");
		SetUsr("");
		SetPass("");
	}

	void SetUserData(int value) 
	{ 
		m_NewItemButton.setUserData(ITEM_INDEX_DATA, reinterpret_cast<QObjectUserData*>(value)); 
		m_RemoveItemButton.setUserData(ITEM_INDEX_DATA, reinterpret_cast<QObjectUserData*>(value)); 
	}
	
	virtual bool eventFilter(QObject* watched, QEvent* event) override;

signals:
	void CheckInputDone();

private slots:
	void OnCheckInputDone();

private:
	void SetupUI();
	void SetupSignal();

private:
	QHBoxLayout m_Layout;

	QLineEdit m_Name;
	QLineEdit m_Url;
	QLineEdit m_Usr;
	QLineEdit m_Pass;
	QPushButton m_SetDefault;
	QPushButton m_NewItemButton;
	QPushButton m_RemoveItemButton;

	ZHttpRequest m_HttpReq;
}; // ZTSettingItem

#endif // ZTSETTING_ITEM_H_
