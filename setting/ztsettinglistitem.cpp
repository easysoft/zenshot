#include "ztsettinglistitem.h"
#include "spdlogwrapper.hpp"

#include <QFile>
#include <QEvent>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

ZTSettingListItem::ZTSettingListItem(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint);

	setMinimumHeight(LISTIEM_MIN_HEIGHT);

	SetupUI();
	SetupSignal();
}

void ZTSettingListItem::SetName(const char* txt)
{
	name_ = txt;

	m_labelName->setText(txt);
	m_labelName->adjustSize();
}

void ZTSettingListItem::SetUrl(const char* url)
{
	url_ = url;

	m_labelUrl->setText(url);
	m_labelUrl->adjustSize();
}

void ZTSettingListItem::SetUsr(const char* usr)
{
	usr_ = usr;
}

void ZTSettingListItem::SetPass(const char* pass)
{
	pass_ = pass;
}

void ZTSettingListItem::SetDefaultItem(bool default)
{
	m_labelDefault->setVisible(default);
}

// void ZTSettingListItem::enterEvent(QEvent* event)
// {
// 	QWidget::enterEvent(event);
// 	m_btnDel.setVisible(true);
// }
// 
// void ZTSettingListItem::leaveEvent(QEvent* event)
// {
// 	QWidget::leaveEvent(event);
// 	m_btnDel.setVisible(false);
// }

void ZTSettingListItem::SetupUI()
{
	// load qss
	QFile file(":/zentaosettinglistitem.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);

	m_labelDefault = findChild<QLabel*>("labelDefault");
	m_labelName = findChild<QLabel*>("labelName");
	m_labelUrl = findChild<QLabel*>("labelUrl");
	m_btnDel = findChild<QPushButton*>("btnDel");

	m_labelDefault->setVisible(false);
}

void ZTSettingListItem::SetupSignal()
{
	connect(m_btnDel, SIGNAL(clicked()), this, SLOT(OnRemoveItem()));
	connect(this, SIGNAL(RemoveItem(ZTSettingListItem*)), parent(), SIGNAL(RemoveListItem(ZTSettingListItem*)));
}

void ZTSettingListItem::OnRemoveItem()
{
	emit RemoveItem(this);
}
