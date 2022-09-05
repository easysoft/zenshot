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
	m_boxProduct = findChild<QComboBox*>("boxProduct");
	m_boxModule = findChild<QComboBox*>("boxModule");
	m_cbxPri = findChild<QComboBox*>("cbxPri");
	m_cbxSeverity = findChild<QComboBox*>("cbxSeverity");
	m_boxVersion = findChild<QComboBox*>("boxVersion");
	m_cbxBrower = findChild<QComboBox*>("cbxBrower");
	m_cbxOS = findChild<QComboBox*>("cbxOS");
	m_cbxType = findChild<QComboBox*>("cbxType");

	m_editTitle = findChild<QLineEdit*>("editTitle");
	m_textDesc = findChild<QTextEdit*>("textDesc");
	m_TimeEditDeadLine = findChild<QDateEdit*>("TimeEditDeadLine");
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
	connect(m_boxProduct, SIGNAL(currentIndexChanged(int index)), this, SLOT(OnProductChanged(int)));
	connect(m_boxModule, SIGNAL(currentIndexChanged(int index)), this, SLOT(OnModuleChanged(int)));
	connect(m_cbxPri, SIGNAL(currentIndexChanged(int index)), this, SLOT(OnPriChanged(int)));
	connect(m_cbxSeverity, SIGNAL(currentIndexChanged(int index)), this, SLOT(OnSeverityChanged(int)));
	connect(m_boxVersion, SIGNAL(currentIndexChanged(int index)), this, SLOT(OnVersionChanged(int)));
}

void ZTBug::OnProductChanged(int index)
{
	m_boxModule->clear();
	m_cbxPri->clear();
	m_cbxSeverity->clear();
	m_boxVersion->clear();
}

void ZTBug::OnModuleChanged(int index)
{
	m_cbxPri->clear();
	m_cbxSeverity->clear();
	m_boxVersion->clear();
}

void ZTBug::OnPriChanged(int index)
{
	m_cbxSeverity->clear();
	m_boxVersion->clear();
}

void ZTBug::OnSeverityChanged(int index)
{
	m_boxVersion->clear();
}

void ZTBug::OnVersionChanged(int index)
{
}

void ZTBug::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}
