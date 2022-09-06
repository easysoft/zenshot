#include "zentaobug.h"

#include "spdlogwrapper.hpp"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

#if !NZENTAO_VER_
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
	connect(m_boxProduct, SIGNAL(currentIndexChanged(int)), this, SLOT(OnProductChanged(int)));
}

void ZTBug::OnBugProductItems(zproduct_item_vec_ptr products)
{
    for (const auto& item : *products)
    {
        m_boxProduct->addItem(item.name_.c_str(), QVariant(item.id_));
    }
}

void ZTBug::OnBugModuleItems(zmodule_item_vec_ptr modules)
{
    for (const auto& item : *modules)
    {
        m_boxModule->addItem(item.name_.c_str(), QVariant(item.id_));
    }
}

void ZTBug::OnBugVersionItems(zversion_item_vec_ptr versions)
{
    for (const auto& item : *versions)
    {
        m_boxVersion->addItem(item.name_.c_str(), QVariant(item.id_));
    }
}

void ZTBug::OnBugPriItems(zpri_item_vec_ptr pris)
{
    for (const auto& item : *pris)
    {
        m_cbxPri->addItem(item.name_.c_str(), QVariant(item.id_));
    }
}

void ZTBug::OnBugSeverityItems(zseverity_item_vec_ptr serveritys)
{
    for (const auto& item : *serveritys)
    {
        m_cbxSeverity->addItem(item.name_.c_str(), QVariant(item.id_));
    }
}

void ZTBug::OnBugOSItems(zos_item_vec_ptr oss)
{
    for (const auto& item : *oss)
    {
        m_cbxOS->addItem(item.name_.c_str(), QVariant(item.id_.c_str()));
    }
}

void ZTBug::OnBugBrowserItems(zbrowser_item_vec_ptr browsers)
{
    for (const auto& item : *browsers)
    {
        m_cbxBrower->addItem(item.name_.c_str(), QVariant(item.id_.c_str()));
    }
}

void ZTBug::OnBugTypeItems(ztype_item_vec_ptr types)
{
    for (const auto& item : *types)
    {
        m_cbxType->addItem(item.name_.c_str(), QVariant(item.id_.c_str()));
    }
}

void ZTBug::OnProductChanged(int index)
{
	m_boxModule->clear();
	m_boxVersion->clear();

    uint32_t product_id = static_cast<uint32_t>(m_boxProduct->itemData(index).toInt());
    emit ProductChanged(product_id, string_ptr(new std::string("bug")));
}

void ZTBug::hideEvent(QHideEvent* event)
{
    QWidget::hideEvent(event);

    m_boxProduct->clear();
    m_boxModule->clear();
    m_cbxPri->clear();
    m_cbxSeverity->clear();
    m_cbxBrower->clear();
    m_cbxOS->clear();
    m_cbxType->clear();
    m_boxVersion->clear();
    m_editTitle->clear();
    m_textDesc->clear();
}

void ZTBug::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}

#endif // NZENTAO_VER_
