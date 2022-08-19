#include "ztsettingItem.h"
#include "spdlogwrapper.hpp"

#include <QFile>
#include <QEvent>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

ZTSettingItem::ZTSettingItem(QWidget* parent)
	: QWidget(parent)
	, m_Layout(this)
	, m_Name(this)
	, m_Url(this)
	, m_Usr(this)
	, m_Pass(this)
	, m_SetDefault(this)
	, m_NewItemButton(this)
	, m_RemoveItemButton(this)
	, m_HttpReq()
{
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	SetupUI();
	SetupSignal();

	installEventFilter(this);
	m_Pass.installEventFilter(this);

	connect(this, SIGNAL(CheckInputDone()), this, SLOT(OnCheckInputDone()));
}

bool ZTSettingItem::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::FocusOut)
	{
		QKeyEvent* e = static_cast<QKeyEvent*>(event);
		if (watched == &m_Pass)
		{
			emit CheckInputDone();
		}
	}

	return QWidget::eventFilter(watched, event);
}

void ZTSettingItem::OnCheckInputDone()
{
	auto name = GetName();
	auto url = GetUrl();
	auto usr = GetUsr();
	auto pass = GetPass();

	if (name.empty() || url.empty() || usr.empty() || pass.empty())
	{
		return;
	}

	auto uri = build_uri(url.c_str(), "/tokens");

	std::string data;
	m_HttpReq.SetUrl(uri.c_str());
	m_HttpReq.SetPost("{\"account\": \"%s\", \"password\": \"%s\"}", usr.c_str(), pass.c_str());
	if (!m_HttpReq.Exec(data))
	{
		return;
	}

	QJsonParseError e;
	QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
	if (doc.isNull() || e.error != QJsonParseError::NoError)
	{
		QMessageBox::information(NULL, tr("Title"), tr("invalid_usr"));
		return;
	}
	
	if (doc["error"].isString())
	{
		QMessageBox::information(NULL, tr("Title"), doc["error"].toString().toUtf8());
		return;
	}

// 	auto token = doc["token"].toString();
// 	if (token.isEmpty())
// 	{
// 		QMessageBox::information(NULL, tr("Title"), tr("invalid_usr"));
// 		return;
// 	}
// 	auto token_str = token.toStdString();
// 
// 	m_HttpReq.SetToken(token_str.c_str());
// 
// 	uri = build_uri(url.c_str(), "/users");
// 	m_HttpReq.SetUrl("%s?page=%d&limit=%d", uri.c_str(), 1, 50);
// 	m_HttpReq.SetTokenHeader();
// 	if (!m_HttpReq.Exec(data))
// 	{
// 		return;
// 	}
// 	doc = QJsonDocument::fromJson(data.c_str(), &e);
// 	if (doc["error"].isString()) 
// 	{
// 		QMessageBox::information(NULL, tr("Title"), doc["error"].toString().toUtf8());
// 	}
// 
// 	uri = build_uri(url.c_str(), "/products");
// 	m_HttpReq.SetUrl(uri.c_str());
// 	m_HttpReq.SetTokenHeader();
// 	if (!m_HttpReq.Exec(data))
// 	{
// 		return;
// 	}
// 	doc = QJsonDocument::fromJson(data.c_str(), &e);
// 
// 	const char* targets[] =
// 	{
// 		"/plans",
// 		"/stories",
// 		"/bugs",
// 	};
// 
// 	int c = 0;
// 	auto products = doc["products"].toArray();
// 	for (const auto& p : products) {
// 		if (c++ >= 100) {
// 			break;
// 		}
// 
// 		auto item = p.toObject();
// 		auto t = item["id"].type();
// 		auto id = item["id"].toInt();
// 
// 		for (int i = 0; i < sizeof(targets) / sizeof(targets[0]); i++)
// 		{
// 			std::string tar;
// 			tar.append("/products/")
// 				.append(std::to_string(id))
// 				.append(targets[i]);
// 			uri = build_uri(url.c_str(), tar.c_str());
// 			m_HttpReq.SetUrl(uri.c_str());
// 			m_HttpReq.SetTokenHeader();
// 			if (!m_HttpReq.Exec(data))
// 			{
// 				return;
// 			}
// 		}
// 	}
// 
// 	uri = build_uri(url.c_str(), "/projects");
// 	m_HttpReq.SetUrl("%s?page=%d&limit=%d", uri.c_str(), 1, 50);
// 	m_HttpReq.SetTokenHeader();
// 	if (!m_HttpReq.Exec(data))
// 	{
// 		return;
// 	}
// 	doc = QJsonDocument::fromJson(data.c_str(), &e);
// 	if (doc["error"].isString())
// 	{
// 		QMessageBox::information(NULL, tr("Title"), doc["error"].toString().toUtf8());
// 	}
// 	const char* targets1[] =
// 	{
// 		"/executions",
// 	};
// 	const char* targets2[] =
// 	{
// 		"/tasks",
// 	};
}

void ZTSettingItem::SetupUI()
{
	setLayout(&m_Layout);

	m_Layout.addWidget(&m_Name, 22);
	m_Layout.addWidget(&m_Url, 22);
	m_Layout.addWidget(&m_Usr, 22);
	m_Layout.addWidget(&m_Pass, 22);

	m_Layout.addWidget(&m_SetDefault, 10);
	m_Layout.addWidget(&m_RemoveItemButton);
	m_Layout.addSpacing(-20);
	m_Layout.addWidget(&m_NewItemButton);

	m_NewItemButton.setObjectName("newItemButton");
	m_RemoveItemButton.setObjectName("removeItemButton");

	m_Name.setPlaceholderText(tr("zentaoname"));
	m_Url.setPlaceholderText(tr("zentaourl"));
	m_Usr.setPlaceholderText(tr("zentaousr"));
	m_Pass.setPlaceholderText(tr("zentaopass"));

	m_Name.setProperty("subitem", "settingitem");
	m_Url.setProperty("subitem", "settingitem");
	m_Usr.setProperty("subitem", "settingitem");
	m_Pass.setProperty("subitem", "settingitem");
	m_Pass.setEchoMode(QLineEdit::Password);

	m_SetDefault.setText(tr("setdefault"));
	m_SetDefault.setCheckable(true);
	m_SetDefault.setProperty("checkbtn", "checkbox");
}

void ZTSettingItem::SetupSignal()
{
	connect(&m_NewItemButton, SIGNAL(clicked()), parent(), SLOT(OnAddNewItem()));
	connect(&m_RemoveItemButton, SIGNAL(clicked()), parent(), SLOT(OnRemoveItem()));
}
