#include "zentaopreview.h"

#include "spdlogwrapper.hpp"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

extern std::string SETTING_XML_NAME;

ZTPreviewDlg::ZTPreviewDlg(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::Tool);

	SetupUI();
	SetupSignal();
}

void ZTPreviewDlg::SetupUI()
{
	// load qss
	QFile file(":/zentaopreview.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);
}

void ZTPreviewDlg::SetupSignal()
{
}

void ZTPreviewDlg::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}
