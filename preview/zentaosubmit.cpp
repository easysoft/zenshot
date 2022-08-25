#include "zentaosubmit.h"

#include "spdlogwrapper.hpp"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

extern std::string SETTING_XML_NAME;

ZTSubmitDlg::ZTSubmitDlg(QWidget* parent)
	: QDialog(parent)
	, m_Preview(nullptr)
	, m_Demand(nullptr)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::Tool);

	InitUI();
	SetupUI();
	SetupSignal();
}

void ZTSubmitDlg::InitUI()
{
	m_framesWidget = findChild<QStackedWidget*>("framesWidget");

	m_framesWidget->addWidget(&m_Preview);
	m_framesWidget->addWidget(&m_Demand);

	m_framesWidget->setCurrentWidget(&m_Preview);
}

void ZTSubmitDlg::SetupUI()
{
	// load qss
	QFile file(":/zentaosubmit.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);
}

void ZTSubmitDlg::SetupSignal()
{
}

void ZTSubmitDlg::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}
