#include "zentaopreview.h"

#include "spdlogwrapper.hpp"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

extern std::string SETTING_XML_NAME;

ZTPreview::ZTPreview(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::Tool);

	SetupUI();
	SetupSignal();
}

void ZTPreview::SetupUI()
{
	// load qss
	QFile file(":/zentaopreview.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);
}

void ZTPreview::SetupSignal()
{
}

void ZTPreview::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}
