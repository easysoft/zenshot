#include "zentaodemand.h"

#include "spdlogwrapper.hpp"
#include "starterui.h"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

extern std::string SETTING_XML_NAME;

ZTDemand::ZTDemand(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::Tool);

	InitUI();
	SetupUI();
}

void ZTDemand::InitUI()
{
	m_boxProduct = findChild<QComboBox*>("boxProduct");
	m_boxModule = findChild<QComboBox*>("boxModule");
	m_boxType = findChild<QComboBox*>("boxType");
	m_boxPri = findChild<QComboBox*>("boxPri");
}

void ZTDemand::SetupUI()
{
	// load qss
	QFile file(":/zentaodemand.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);
}

void ZTDemand::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}
