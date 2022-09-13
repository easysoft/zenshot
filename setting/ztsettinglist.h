#ifndef ZTSETTING_LIST_H_
#define ZTSETTING_LIST_H_

#include "ui_zentaosettinglist.h"

#include "ztsettinglistitem.h"

#include "usrmetatype.h"

#include <QListWidget>

class ZTSettingList : public QWidget {
	Q_OBJECT

public:
	ZTSettingList(QWidget* parent);
	~ZTSettingList() {}

	int currentRow()
	{
		return m_listWidget->currentRow();
	}

	void AddNewRow(const std::string& name, const std::string& url, const std::string& usr, const std::string& pass)
	{
		QListWidgetItem* item = nullptr;
		ZTSettingListItem* w = nullptr;
		item = m_listWidget->item(m_listWidget->count() - 1);
		if (item && item->isHidden())
		{
			w = static_cast<ZTSettingListItem*>(m_listWidget->itemWidget(item));
			if (w != nullptr)
			{
				const char* name = w->GetName();
				const char* url = w->GetUrl();
				const char* usr = w->GetUsr();
				const char* pass = w->GetPass();
				if (!name[0] || !url[0] || !usr[0] || !pass[0])
				{
					item = new QListWidgetItem(m_listWidget);
					item->setSizeHint(QSize(m_listWidget->width(), LISTIEM_MIN_HEIGHT));

					w = new ZTSettingListItem(this);
					m_listWidget->setItemWidget(item, w);
					item->setHidden(false);
				}
			}
		}
		else
		{
			item = new QListWidgetItem(m_listWidget);
			item->setSizeHint(QSize(m_listWidget->width(), LISTIEM_MIN_HEIGHT));

			w = new ZTSettingListItem(this);
			m_listWidget->setItemWidget(item, w);
			item->setHidden(false);
		}

		w->SetName(name.c_str());
		w->SetUrl(url.c_str());
		w->SetUsr(usr.c_str());
		w->SetPass(pass.c_str());

		w->SetDefaultItem(true);
	}
signals:
	void AddConfigItem(string_ptr name, string_ptr url, string_ptr usr, string_ptr pass);
	void SaveSiteListConfig();
	void CurrentRowSelected(int index, string_ptr name, string_ptr url, string_ptr usr, string_ptr pass);
	void RemoveListItem(ZTSettingListItem* item);
	void SelectDefault();
	void SetDefaultSiteName(string_ptr name);

private slots:
	void OnRealRemoveItem(ZTSettingListItem* w);
	void OnAddConfigItem(string_ptr name, string_ptr url, string_ptr usr, string_ptr pass);
	void OnSaveSiteListConfig();
	void OncurrentRowChanged(int index);
	void OnNewSiteConfig();

	void OnUpdateName(const QString& name);
	void OnUpdateUrl(const QString& url);
	void OnUpdateUsr(const QString& usr);
	void OnUpdatePass(const QString& pass);

	void OnSelectDefault();
	void OnSetDefaultItem(bool default);

protected:
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void showEvent(QShowEvent* event) override;
	virtual void hideEvent(QHideEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	void InitUI();
	void SetupUI();
	void SetupSignal();

	QListWidgetItem* FindHiddenItem();

private:
	Ui::zentaosettinglist ui;

	QListWidget* m_listWidget;
}; // ZTSettingList

#endif // ZTSETTING_LIST_H_
