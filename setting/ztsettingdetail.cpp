#include "ztsettingdetail.h"
#include "spdlogwrapper.hpp"

#include <QFile>
#include <QEvent>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

ZTSettingDetail::ZTSettingDetail(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint);

	InitUI();
	SetupUI();
	SetupSignal();
// 
// 	installEventFilter(this);
// 	m_Pass.installEventFilter(this);
// 
	connect(this, SIGNAL(CheckInputDone()), this, SLOT(OnCheckInputDone()));
	connect(this, SIGNAL(ChangeCurrentSelectDetail(string_ptr, string_ptr, string_ptr, string_ptr)), this, SLOT(OnChangeCurrentSelectDetail(string_ptr, string_ptr, string_ptr, string_ptr)));
}

// bool ZTSettingDetail::eventFilter(QObject* watched, QEvent* event)
// {
// 	if (event->type() == QEvent::FocusOut)
// 	{
// // 		QKeyEvent* e = static_cast<QKeyEvent*>(event);
// 		if (watched == &m_Pass)
// 		{
// 			emit CheckInputDone();
// 		}
// 	}
// 
// 	return QWidget::eventFilter(watched, event);
// }

void ZTSettingDetail::OnCheckInputDone()
{
// 	auto name = GetName();
// 	auto url = GetUrl();
// 	auto usr = GetUsr();
// 	auto pass = GetPass();
// 
// 	if (name.empty() || url.empty() || usr.empty() || pass.empty())
// 	{
// 		return;
// 	}
// 
// 	auto uri = build_uri(url.c_str(), "/tokens");
// 
// 	std::string data;
// 	m_HttpReq.SetUrl(uri.c_str());
// 	m_HttpReq.SetPost("{\"account\": \"%s\", \"password\": \"%s\"}", usr.c_str(), pass.c_str());
// 	if (!m_HttpReq.Exec(data))
// 	{
// 		return;
// 	}
// 
// 	QJsonParseError e;
// 	QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
// 	if (doc.isNull() || e.error != QJsonParseError::NoError)
// 	{
// 		QMessageBox::information(NULL, tr("Title"), tr("invalid_usr"));
// 		return;
// 	}
// 	
// 	if (doc["error"].isString())
// 	{
// 		QMessageBox::information(NULL, tr("Title"), doc["error"].toString().toUtf8());
// 		return;
// 	}

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

void ZTSettingDetail::OnChangeCurrentSelectDetail(string_ptr name, string_ptr url, string_ptr usr, string_ptr pass)
{
	m_textName->setText(name->c_str());
	m_textUri->setText(url->c_str());
	m_textUsr->setText(usr->c_str());
	m_textPass->setText(pass->c_str());
}

void ZTSettingDetail::InitUI()
{
	m_checkSetDefault = findChild<QCheckBox*>("checkSetDefault");
	
	m_labelNameTitle = findChild<QLabel*>("labelNameTitle");
	m_labelUriTitle = findChild<QLabel*>("labelUriTitle");
	m_labelUsr = findChild<QLabel*>("labelUsr");
	m_labelPass = findChild<QLabel*>("labelPass");

	m_btnSave = findChild<QPushButton*>("btnSave");
	m_btnNew = findChild<QPushButton*>("btnNew");

	m_textName = findChild<QLineEdit*>("textName");
	m_textUri = findChild<QLineEdit*>("textUri");
	m_textUsr = findChild<QLineEdit*>("textUsr");
	m_textPass = findChild<QLineEdit*>("textPass");
}

void ZTSettingDetail::SetupUI()
{
	// load qss
	QFile file(":/zentaosettingdetail.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);
}

void ZTSettingDetail::SetupSignal()
{
// 	connect(&m_NewItemButton, SIGNAL(clicked()), parent(), SLOT(OnAddNewItem()));
// 	connect(&m_RemoveItemButton, SIGNAL(clicked()), parent(), SLOT(OnRemoveItem()));
}
