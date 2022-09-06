#include "ztsettinglist.h"

#include "config/xmlconfig.h"
#include "config/configvalue.h"
#include "spdlogwrapper.hpp"

#include <QFile>
#include <QEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QScrollBar>
#include <QStringList>
#include <QStringListModel>

extern std::string SETTING_XML_NAME;

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
	auto each_node = [this](rapidxml::xml_node<>* root, rapidxml::xml_node<>* node)
	{
		(void*)root;

		std::string name = GetConfigAttrString(node, "name"),
			url = GetConfigAttrString(node, "url"),
			usr = GetConfigAttrString(node, "usr"),
			pass = GetConfigAttrString(node, "pass");
		if (url.empty())
		{
			return false;
		}

		std::string real_pass;
		for (auto it = pass.begin(); it != pass.end(); it += 2)
		{
			int c;
			sscanf(&*it, "%02X", &c);
			c ^= 2;
			real_pass.push_back((char)c);
		}
		real_pass.push_back('\0');

		emit AddConfigItem(string_ptr(new std::string(name)), string_ptr(new std::string(url)), string_ptr(new std::string(usr)), string_ptr(new std::string(pass)));
		return false;
	};

	// read config
	GetXMLConfig().FindAllNode("config", "zentao", each_node);

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
	std::string name;
	auto remove_name_node = [&](rapidxml::xml_node<>* root, rapidxml::xml_node<>* node)
	{
		std::string n = GetConfigAttrString(node, "name");
		if (name == n)
		{
			RemoveNode(root, node);
			return true;
		}

		return false;
	};
	for (int i = 0; i < m_listWidget->count(); i++)
	{
		auto item = m_listWidget->item(i);
		auto w1 = m_listWidget->itemWidget(item);
		if (w1 == w)
		{
			item->setHidden(true);

			GetXMLConfig().FindAllNode("config", "zentao", remove_name_node);
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
	if (w == nullptr)
	{
		w = new ZTSettingListItem(this);
		m_listWidget->setItemWidget(item, w);
	}

	w->SetName(name->c_str());
	w->SetUrl(url->c_str());
	w->SetUsr(usr->c_str());
	w->SetPass(pass->c_str());

	item->setHidden(false);
}

void ZTSettingList::OnSaveSiteListConfig()
{
	// remove all node
	GetXMLConfig().RemoveAllNode("config", "zentao");

	for (int i = 0; i < m_listWidget->count(); i++)
	{
		auto item = m_listWidget->item(i);
		if (item->isHidden())
		{
			continue;
		}

		auto w = static_cast<ZTSettingListItem*>(m_listWidget->itemWidget(item));

		auto node = GetXMLConfig().AddConfigString3("config", "zentao", "name", w->GetName());
		AddConfigAttrStr(node, "url", w->GetUrl());
		AddConfigAttrStr(node, "usr", w->GetUsr());

// 		std::string orig_pass = w->GetPass();
		std::string pass = w->GetPass();
// 		for (char c : orig_pass)
// 		{
// 			uint8_t u = (uint8_t)c;
// 			u ^= 2;
// 
// 			char buf[3] = { 0 };
// 			sprintf(buf, "%02X", u);
// 			pass.append(buf);
// 		}
		AddConfigAttrStr(node, "pass", pass.c_str());
	}

	GetXMLConfig().SaveConfig(SETTING_XML_NAME);
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
	GetXMLConfig().SaveConfig(SETTING_XML_NAME);
}

void ZTSettingList::OnNewSiteConfig()
{
	// check if empty
	{
		auto item = m_listWidget->item(m_listWidget->count() - 1);
		auto w = static_cast<ZTSettingListItem*>(m_listWidget->itemWidget(item));
		if (w != nullptr)
		{
			const char* name = w->GetName();
			const char* url = w->GetUrl();
			const char* usr = w->GetUsr();
			const char* pass = w->GetPass();
			if (!name[0] || !url[0] || !usr[0] || !pass[0])
			{
				return;
			}
		}
	}

	auto item = new QListWidgetItem(m_listWidget);
	item->setSizeHint(QSize(m_listWidget->width(), LISTIEM_MIN_HEIGHT));
	m_listWidget->addItem(item);
	auto w = new ZTSettingListItem(this);
	m_listWidget->setItemWidget(item, w);
	item->setHidden(false);

	m_listWidget->setCurrentItem(item);
}
