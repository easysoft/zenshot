#include "ztsettinglist.h"

#include "config/xmlconfig.h"
#include "spdlogwrapper.hpp"

#include <QFile>
#include <QEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QScrollBar>
#include <QStringList>
#include <QStringListModel>

ZTSettingList::ZTSettingList(QWidget* parent)
	: QWidget(parent)
{
	qRegisterMetaType<ZTSettingListItem*>("ZTSettingListItem*");

	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint);

	InitUI();
	SetupUI();
	SetupSignal();
}

void ZTSettingList::InitUI()
{
	m_listWidget = findChild<QListWidget*>("listWidget");
}

void ZTSettingList::SetupUI()
{
	// load qss
	QFile file(":/zentaosettinglist.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);
}

void ZTSettingList::SetupSignal()
{
	connect(this, SIGNAL(AddConfigItem(string_ptr, string_ptr, string_ptr, string_ptr)), this, SLOT(OnAddConfigItem(string_ptr, string_ptr, string_ptr, string_ptr)));
	connect(this, SIGNAL(SaveSiteListConfig()), this, SLOT(OnSaveSiteListConfig()));
	connect(m_listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(OncurrentRowChanged(int)));
}

QListWidgetItem* ZTSettingList::FindHiddenItem()
{
	for (int i = 0; i < m_listWidget->count(); i++) 
	{
		auto item = m_listWidget->item(i);
		if (item->isHidden())
		{
			return item;
		}
	}

	return nullptr;
}

void ZTSettingList::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ZTSettingList::showEvent(QShowEvent* event)
{
	// read config
	int index = 0;
	std::string real_pass;
	for (;; index++)
	{
		std::string zentao = BuildConfigKey(index);
		std::string name = GetXMLConfig().GetConfigString3("config", zentao.c_str(), "name"),
			url = GetXMLConfig().GetConfigString3("config", zentao.c_str(), "url"),
			usr = GetXMLConfig().GetConfigString3("config", zentao.c_str(), "usr"),
			pass = GetXMLConfig().GetConfigString3("config", zentao.c_str(), "pass");
		if (url.empty())
		{
			break;
		}

		real_pass.clear();
		for (auto it = pass.begin(); it != pass.end(); it += 2)
		{
			int c;
			sscanf(&*it, "%02X", &c);
			c ^= 2;
			real_pass.push_back((char)c);
		}
		real_pass.push_back('\0');

		emit AddConfigItem(string_ptr(new std::string(name)), string_ptr(new std::string(url)), string_ptr(new std::string(usr)), string_ptr(new std::string(pass)));
	}

	QWidget::showEvent(event);
}

void ZTSettingList::hideEvent(QHideEvent* event)
{
	QWidget::hideEvent(event);

	for (int i = m_listWidget->count() - 1; i >= 0; i--)
	{
		auto item = m_listWidget->item(i);
		item->setHidden(true);
	}
}

void ZTSettingList::closeEvent(QCloseEvent* event)
{
	event->ignore();

	hide();
}

void ZTSettingList::OnRealRemoveItem(ZTSettingListItem* w)
{
	for (int i = 0; i < m_listWidget->count(); i++)
	{
		auto item = m_listWidget->item(i);
		auto w1 = m_listWidget->itemWidget(item);
		if (w1 == w)
		{
			item->setHidden(true);

			std::string key = BuildConfigKey(i);
			GetXMLConfig().RemoveConfig2("config", key.c_str());
			GetXMLConfig().SaveConfig(SETTING_XML_NAME);
			break;
		}
	}
}

void ZTSettingList::OnAddConfigItem(string_ptr name, string_ptr url, string_ptr usr, string_ptr pass)
{
	auto item = FindHiddenItem();
	if (!item)
	{
		item = new QListWidgetItem(m_listWidget);
		item->setSizeHint(QSize(m_listWidget->width(), LISTIEM_MIN_HEIGHT));
		m_listWidget->addItem(item);
	}
	auto w = static_cast<ZTSettingListItem*>(m_listWidget->itemWidget(item));
	if (w)
	{
		m_listWidget->removeItemWidget(item);
	}
	else
	{
		w = new ZTSettingListItem(this);
		m_listWidget->setItemWidget(item, w);
	}

	w->SetName(name->c_str());
	w->SetUrl(url->c_str());
	w->SetUsr(usr->c_str());
	w->SetPass(pass->c_str());

	m_listWidget->setItemWidget(item, w);
	item->setHidden(false);
}

void ZTSettingList::OnSaveSiteListConfig()
{
}

void ZTSettingList::OncurrentRowChanged(int index)
{
	if (index == -1)
	{
		return;
	}

	auto item = m_listWidget->item(index);
	auto w = static_cast<ZTSettingListItem*>(m_listWidget->itemWidget(item));

	string_ptr name(new std::string(w->GetName()));
	string_ptr url(new std::string(w->GetUrl()));
	string_ptr usr(new std::string(w->GetUsr()));
	string_ptr pass(new std::string(w->GetPass()));
	emit CurrentRowSelected(name, url, usr, pass);
}

void ZTSettingList::OnSaveSiteConfig()
{
	int index = 0;
	for (int i = 0; i < m_listWidget->count(); i++)
	{
		auto item = m_listWidget->item(i);
		if (item->isHidden())
			continue;

		auto w = static_cast<ZTSettingListItem*>(m_listWidget->itemWidget(item));
		if (!w)
			continue;

		std::string key = BuildConfigKey(index);
		std::string name = w->GetName();
		std::string url = w->GetUrl();
		std::string usr = w->GetUsr();
		std::string pass = w->GetPass();
	}
}
