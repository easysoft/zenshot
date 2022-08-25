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
	, m_Layer(this)
	, m_labelName(this)
	, m_btnDel(this)
{
	setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint);

	setMinimumHeight(LISTIEM_MIN_HEIGHT);

	SetupUI();
	SetupSignal();
}

void ZTSettingListItem::SetName(const char* txt)
{
	name_ = txt;
	m_labelName.setText(txt);
}

void ZTSettingListItem::SetUrl(const char* url)
{
	url_ = url;
}

void ZTSettingListItem::SetUsr(const char* usr)
{
	usr_ = usr;
}

void ZTSettingListItem::SetPass(const char* pass)
{
	pass_ = pass;
}

void ZTSettingListItem::enterEvent(QEvent* event)
{
	QWidget::enterEvent(event);
	m_btnDel.setVisible(true);
}

void ZTSettingListItem::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
	m_btnDel.setVisible(false);
}

void ZTSettingListItem::SetupUI()
{
	setLayout(&m_Layer);
	m_Layer.setSpacing(0);
	m_Layer.setContentsMargins(0, 0, 18, 30);

	m_labelName.setMinimumHeight(LISTIEM_MIN_HEIGHT);
	m_btnDel.setMinimumHeight(LISTIEM_MIN_HEIGHT);

	m_labelName.setAlignment(Qt::AlignVCenter);
	m_labelName.setProperty("class", "listItemTxt");
	m_btnDel.setProperty("class", "listItemBtn");
	m_btnDel.setVisible(false);

	m_Layer.addWidget(&m_labelName, 8, Qt::AlignLeft | Qt::AlignVCenter);
	m_Layer.addWidget(&m_btnDel, 2, Qt::AlignRight | Qt::AlignVCenter);
}

void ZTSettingListItem::SetupSignal()
{
	connect(&m_btnDel, SIGNAL(clicked()), this, SLOT(OnRemoveItem()));
	connect(this, SIGNAL(RemoveItem(ZTSettingListItem*)), parent(), SLOT(OnRealRemoveItem(ZTSettingListItem*)));
}

void ZTSettingListItem::OnRemoveItem()
{
	emit RemoveItem(this);
}
