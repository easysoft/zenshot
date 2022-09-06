#include "zentaosetting.h"

#include "ztsettingdetail.h"
#include "config/xmlconfig.h"
#include "config/configvalue.h"
#include "spdlogwrapper.hpp"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

#if !NZENTAO_VER_
extern std::string SETTING_XML_NAME;

ZTSettingDlg::ZTSettingDlg(QWidget* parent)
	: QDialog(parent)
    , m_Layout()
	, m_Detail(nullptr)
    , m_List(nullptr)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::Tool);

	SetupUI();
	SetupSignal();
}

void ZTSettingDlg::OnAddNewItem()
{
// 	int w = CalcRowWidth(),
// 		h = CalcRowHeight();
// 	QPushButton* btn = static_cast<QPushButton*>(sender());
// 	int index = btn ? reinterpret_cast<int>(btn->userData(ITEM_INDEX_DATA)) : m_ZTSettingList.count();
// 	QListWidgetItem* item = m_ZTSettingList.item(index + 1);
// 	if (item && item->isHidden())
// 	{
// 		ZTSettingItem* zw = static_cast<ZTSettingItem*>(m_ZTSettingList.itemWidget(item));
// 		zw->Clear();
// 
// 		item->setHidden(false);
// 		return;
// 	}
// 
// 	L_TRACE("++++++++++++++++++++++++++++++++++++++++++++ index {0} & count {1}", index, m_ZTSettingList.count());
// 	
// 	item = new QListWidgetItem;
// 	item->setSizeHint(QSize(w, h));
// 	m_ZTSettingList.insertItem(index + 1, item);
// 
// 	ZTSettingItem* zw = new ZTSettingItem(this);
// 	m_ZTSettingList.setItemWidget(item, zw);
// 
// 	for (int i = m_ZTSettingList.count() - 1; i >= index; i--)
// 	{
// 		ResetItemData(i, i);
// 	}
}

void ZTSettingDlg::OnRemoveItem()
{
// 	QPushButton* btn = static_cast<QPushButton*>(sender());
// 	if (!btn)
// 	{
// 		return;
// 	}
// 
// 	int index = reinterpret_cast<int>(btn->userData(ITEM_INDEX_DATA));
// 
// 	QListWidgetItem* item = m_ZTSettingList.item(index);
// 	item->setHidden(true);
}

void ZTSettingDlg::OnConfigCancel()
{
	hide();
}

void ZTSettingDlg::OnConfigSave()
{
	emit SaveZentaoSiteConfig();
	emit SaveZentaoDefaultSite();
}

void ZTSettingDlg::OnConfigNew()
{
}

void ZTSettingDlg::OnCheckConfig()
{
}

void ZTSettingDlg::SetupUI()
{
	// load qss
	QFile file(":/zentaosetting.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);

	setLayout(&m_Layout);
	m_Layout.setSpacing(0);
	m_Layout.setContentsMargins(40, 30, 40, 30);

	m_Layout.addWidget(&m_Detail, 57);
	m_Layout.addWidget(&m_List, 43);
}

void ZTSettingDlg::SetupSignal()
{
	connect(this, SIGNAL(AddNewItem()), this, SLOT(OnAddNewItem()));
	connect(this, SIGNAL(RemoveItem()), this, SLOT(OnRemoveItem()));

	connect(this, SIGNAL(ConfigCancel()), this, SLOT(OnConfigCancel()));
	connect(&m_Detail, SIGNAL(ConfigSave()), this, SLOT(OnConfigSave()));

	connect(&m_List, SIGNAL(CurrentRowSelected(string_ptr, string_ptr, string_ptr, string_ptr)), &m_Detail, SIGNAL(ChangeCurrentSelectDetail(string_ptr, string_ptr, string_ptr, string_ptr)));

	connect(this, SIGNAL(SaveZentaoSiteConfig()), &m_List, SIGNAL(SaveSiteListConfig()));
	connect(this, SIGNAL(SaveZentaoDefaultSite()), &m_Detail, SIGNAL(SaveDefaultSite()));

	connect(&m_Detail, SIGNAL(ConfigNew()), &m_List, SLOT(OnNewSiteConfig()));
}

// {
// 	bool done = false;
// 	auto default_cb = [&](rapidxml::xml_node<>* root, rapidxml::xml_node<>* node)
// 	{
// 		(void*)root;
// 
// 		SetConfigStr(node, "default", m_DefaultUrl.c_str());
// 		done = true;
// 		return true;
// 	};
// 	GetXMLConfig().FindAllNode("config", "default", default_cb);
// }

int ZTSettingDlg::CalcRowWidth()
{
	return 100;
// 	int w = m_ZTSettingList.size().width() - 20;
// 	return w;
}

int ZTSettingDlg::CalcRowHeight()
{
	return 100;
// 	int h = m_ZTSettingList.size().height();
// 	h -= 20;
// 	h /= 3;
// 	return h;
}

void ZTSettingDlg::ResetItem(int index, const char* name, const char* url, const char* usr, const char* pass)
{
// 	QListWidgetItem* item = m_ZTSettingList.item(index);
// 	if (!item)
// 	{
// 		return;
// 	}
// 
// 	ZTSettingItem* w = static_cast<ZTSettingItem*>(m_ZTSettingList.itemWidget(item));
// 	w->SetName(name);
// 	w->SetUrl(url);
// 	w->SetUsr(usr);
// 	w->SetPass(pass);
}

void ZTSettingDlg::ResetItemData(int index, int value)
{
// 	QListWidgetItem* item = m_ZTSettingList.item(index);
// 	if (!item)
// 	{
// 		return;
// 	}
// 
// 	ZTSettingItem* w = static_cast<ZTSettingItem*>(m_ZTSettingList.itemWidget(item));
// 	w->SetUserData(value);
}

// void ZTSettingDlg::paintEvent(QPaintEvent* event)
// {
// 	QPainter painter(this);
// 	painter.setRenderHint(QPainter::Antialiasing);
// 	painter.setBrush(QBrush(Qt::white));
// 	painter.setPen(Qt::transparent);
// 	QRect rect = this->rect();
// 	rect.setWidth(rect.width() - 1);
// 	rect.setHeight(rect.height() - 1);
// 	painter.drawRoundedRect(rect, 10, 10);
// 
// 	QWidget::paintEvent(event);
// }

// void ZTSettingDlg::showEvent(QShowEvent* event)
// {
// 	L_TRACE("###############################################################################");
// 	int index = 0;
// // 	if (!m_ZTSettingList.count())
// // 	{
// 		std::string real_pass;
// 		for (;; index++)
// 		{
// 			std::string zentao = BuildConfigKey(index);
// 			std::string name = GetXMLConfig().GetConfigString3("config", zentao.c_str(), "name"),
// 				url = GetXMLConfig().GetConfigString3("config", zentao.c_str(), "url"),
// 				usr = GetXMLConfig().GetConfigString3("config", zentao.c_str(), "usr"),
// 				pass = GetXMLConfig().GetConfigString3("config", zentao.c_str(), "pass");
// 			if (url.empty())
// 			{
// 				break;
// 			}
// 
// 			OnAddNewItem();
// 			real_pass.clear();
// 			for (auto it = pass.begin(); it != pass.end(); it += 2)
// 			{
// 				int c;
// 				sscanf(&*it, "%02X", &c);
// 				c ^= 2;
// 				real_pass.push_back((char)c);
// 			}
// 			real_pass.push_back('\0');
// 			ResetItem(m_ZTSettingList.count() - 1, name.c_str(), url.c_str(), usr.c_str(), real_pass.c_str());
// 		}
// 	}
// // 	
// // 	for (index; index < 3; index++)
// // 	{
// // 		OnAddNewItem();
// // 	}
// 
// 	L_TRACE("###############################################################################");
// 	QWidget::showEvent(event);
// }

void ZTSettingDlg::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}

#endif // NZENTAO_VER_