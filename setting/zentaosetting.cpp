#include "zentaosetting.h"

#include "ztsettingItem.h"
#include "config/xmlconfig.h"
#include "spdlogwrapper.hpp"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

extern std::string SETTING_XML_NAME;

static std::string BuildConfigKey(int index);

ZTSettingDlg::ZTSettingDlg(QWidget* parent)
	: QWidget(parent)
	, m_Layout(this)
	, m_ButtonLayout(this)
	, m_Title(this)
	, m_ZTSettingList(this)
	, m_SaveButton(this)
	, m_CancelButton(this)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	SetupUI();
	SetupSignal();
}

void ZTSettingDlg::OnAddNewItem()
{
	int w = CalcRowWidth(),
		h = CalcRowHeight();
	QPushButton* btn = static_cast<QPushButton*>(sender());
	int index = btn ? reinterpret_cast<int>(btn->userData(ITEM_INDEX_DATA)) : m_ZTSettingList.count();
	QListWidgetItem* item = m_ZTSettingList.item(index + 1);
	if (item && item->isHidden())
	{
		ZTSettingItem* zw = static_cast<ZTSettingItem*>(m_ZTSettingList.itemWidget(item));
		zw->Clear();

		item->setHidden(false);
		return;
	}

	L_TRACE("++++++++++++++++++++++++++++++++++++++++++++ index {0} & count {1}", index, m_ZTSettingList.count());
	
	item = new QListWidgetItem;
	item->setSizeHint(QSize(w, h));
	m_ZTSettingList.insertItem(index + 1, item);

	ZTSettingItem* zw = new ZTSettingItem(this);
	m_ZTSettingList.setItemWidget(item, zw);

	for (int i = m_ZTSettingList.count() - 1; i >= index; i--)
	{
		ResetItemData(i, i);
	}
}

void ZTSettingDlg::OnRemoveItem()
{
	QPushButton* btn = static_cast<QPushButton*>(sender());
	if (!btn)
	{
		return;
	}

	int index = reinterpret_cast<int>(btn->userData(ITEM_INDEX_DATA));

	QListWidgetItem* item = m_ZTSettingList.item(index);
	item->setHidden(true);
}

void ZTSettingDlg::OnButtonCancel()
{
	hide();
}

void ZTSettingDlg::OnButtonSave()
{
	// remove all config
	int index = 0;
	for (;; index++)
	{
		std::string k = BuildConfigKey(index);
		std::string url = GetXMLConfig().GetConfigString3("config", k.c_str(), "url");
		if (url.empty())
		{
			break;
		}

		GetXMLConfig().RemoveConfig2("config", k.c_str());
	}
	
	index = 0;
	for (int i = 0; i < m_ZTSettingList.count(); i++)
	{
		QListWidgetItem* item = m_ZTSettingList.item(i);
		if (item->isHidden())
		{
			continue;
		}

		if (!SaveConfig(i, index))
		{
			continue;
		}

		index++;
	}

	GetXMLConfig().SaveConfig(SETTING_XML_NAME);
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

	m_Title.setObjectName("titleLabel");
	m_Title.setText(tr("title"));

	setLayout(&m_Layout);
	m_ButtonLayout.addSpacing(300);
	m_ButtonLayout.addWidget(&m_CancelButton);
	m_ButtonLayout.addWidget(&m_SaveButton);
	m_ButtonLayout.addSpacing(300);

	m_Layout.addWidget(&m_Title, 10, Qt::AlignCenter);
	m_Layout.addWidget(&m_ZTSettingList, 80);
	m_Layout.addLayout(&m_ButtonLayout, 10);

	m_ZTSettingList.setFrameShape(QListWidget::NoFrame);
	m_SaveButton.setObjectName("settingSaveBtn");
	m_CancelButton.setObjectName("settingCancelBtn");

	m_SaveButton.setText(tr("save"));
	m_CancelButton.setText(tr("cancel"));
}

void ZTSettingDlg::SetupSignal()
{
	connect(this, SIGNAL(AddNewItem()), this, SLOT(OnAddNewItem()));
	connect(this, SIGNAL(RemoveItem()), this, SLOT(OnRemoveItem()));

	connect(&m_CancelButton, SIGNAL(clicked()), this, SLOT(OnButtonCancel()));
	connect(&m_SaveButton, SIGNAL(clicked()), this, SLOT(OnButtonSave()));
}

bool ZTSettingDlg::SaveConfig(int index, int config_index)
{
	QListWidgetItem* item = m_ZTSettingList.item(index);
	if (!item) 
	{
		return false;
	}

	ZTSettingItem* w = static_cast<ZTSettingItem*>(m_ZTSettingList.itemWidget(item));
	auto name = w->GetName();
	auto url = w->GetUrl();
	auto usr = w->GetUsr();
	auto pass = w->GetPass();

	if (url.empty())
	{
		return false;
	}

	std::string new_pass;
	std::for_each(pass.begin(), pass.end(), [&new_pass](const char ch)
		{
			uint8_t c = (uint8_t)ch;
			c ^= 2;
			char buf[3] = { 0 };
			sprintf(buf, "%02X", c);

			new_pass.append(buf);
		});

	std::string zentao = BuildConfigKey(config_index);

	GetXMLConfig().SetConfigString3("config", zentao.c_str(), "name", name.c_str());
	GetXMLConfig().SetConfigString3("config", zentao.c_str(), "url", url.c_str());
	GetXMLConfig().SetConfigString3("config", zentao.c_str(), "usr", usr.c_str());
	GetXMLConfig().SetConfigString3("config", zentao.c_str(), "pass", new_pass.c_str());

	return true;
}

void ZTSettingDlg::SaveDefaultConfig(int index)
{
	std::string zentao = BuildConfigKey(index);
	GetXMLConfig().SetConfigString3("config", "zentao", "default", zentao.c_str());
}

int ZTSettingDlg::CalcRowWidth()
{
	int w = m_ZTSettingList.size().width() - 20;
	return w;
}

int ZTSettingDlg::CalcRowHeight()
{
	int h = m_ZTSettingList.size().height();
	h -= 20;
	h /= 3;
	return h;
}

void ZTSettingDlg::ResetItem(int index, const char* name, const char* url, const char* usr, const char* pass)
{
	QListWidgetItem* item = m_ZTSettingList.item(index);
	if (!item)
	{
		return;
	}

	ZTSettingItem* w = static_cast<ZTSettingItem*>(m_ZTSettingList.itemWidget(item));
	w->SetName(name);
	w->SetUrl(url);
	w->SetUsr(usr);
	w->SetPass(pass);
}

void ZTSettingDlg::ResetItemData(int index, int value)
{
	QListWidgetItem* item = m_ZTSettingList.item(index);
	if (!item)
	{
		return;
	}

	ZTSettingItem* w = static_cast<ZTSettingItem*>(m_ZTSettingList.itemWidget(item));
	w->SetUserData(value);
}

void ZTSettingDlg::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(QBrush(Qt::white));
	painter.setPen(Qt::transparent);
	QRect rect = this->rect();
	rect.setWidth(rect.width() - 1);
	rect.setHeight(rect.height() - 1);
	painter.drawRoundedRect(rect, 10, 10);

	QWidget::paintEvent(event);
}

void ZTSettingDlg::showEvent(QShowEvent* event)
{
	L_TRACE("###############################################################################");
	int index = 0;
	if (!m_ZTSettingList.count())
	{
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

			OnAddNewItem();
			real_pass.clear();
			for (auto it = pass.begin(); it != pass.end(); it += 2)
			{
				int c;
				sscanf(&*it, "%02X", &c);
				c ^= 2;
				real_pass.push_back((char)c);
			}
			real_pass.push_back('\0');
			ResetItem(m_ZTSettingList.count() - 1, name.c_str(), url.c_str(), usr.c_str(), real_pass.c_str());
		}
	}
	
	for (index; index < 3; index++)
	{
		OnAddNewItem();
	}

	L_TRACE("###############################################################################");
	QWidget::showEvent(event);
}

void ZTSettingDlg::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}

static std::string BuildConfigKey(int index)
{
	return "zentao" + std::to_string(index);
}
