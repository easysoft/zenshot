#include "zentaobug.h"

#include "spdlogwrapper.hpp"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

extern std::string SETTING_XML_NAME;

ZTBug::ZTBug(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::Tool);

	InitUI();
	SetupUI();
	SetupSignal();
}

void ZTBug::InitUI()
{
}

void ZTBug::SetupUI()
{
	// load qss
	QFile file(":/zentaobug.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);
}

void ZTBug::SetupSignal()
{
}

void ZTBug::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}
