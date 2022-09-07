#include "zentaodemand.h"

#include "spdlogwrapper.hpp"
#include "starterui.h"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QJsonObject>
#include <QJsonDocument>

#if !NZENTAO_VER_
extern std::string SETTING_XML_NAME;

ZTDemand::ZTDemand(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::Tool);

	InitUI();
	SetupUI();
    SetupSignal();
}

uint32_t ZTDemand::BuildDemandJson(const std::string& img, string_ptr json)
{
    /*
    {
        "title": "²âÊÔÐèÇó",
        "spec": "²âÊÔ",
        "product": 1,
        "pri": 1,
        "category": "feature"
    }
    */
    int product_id = m_boxProduct->currentData().toInt();
    int module_id = m_boxModule->currentData().toInt();
    int pri_id = m_boxPri->currentData().toInt();
    QString type_id = m_boxType->currentData().toString();

    auto story = m_editStory->text().toDouble();
    QString title = m_editTitle->text().toUtf8();

    QString desc;
    if (!img.empty())
    {
        desc.append("<img src=")
            .append("\"").append(img.c_str()).append("\"")
            .append(" alt ")
            .append("/>")
            .append("\n");
    }
    desc.append(m_textDesc->toPlainText().toUtf8());
    QString verify = m_texVerify->toPlainText().toUtf8();

    desc.replace("\r\n", "<br>");
    desc.replace("\n", "<br>");
    verify.replace("\r\n", "<br>");
    verify.replace("\n", "<br>");

    QJsonObject obj;
    obj.insert("title", title);
    obj.insert("spec", desc);
    obj.insert("category", type_id);
    obj.insert("verify", verify);
    obj.insert("product", product_id);
    obj.insert("pri", pri_id);

    QJsonDocument doc;
    doc.setObject(obj);
    *json = doc.toJson(QJsonDocument::Compact).toStdString();

    return product_id;
}

void ZTDemand::InitUI()
{
	m_boxProduct = findChild<QComboBox*>("boxProduct");
	m_boxModule = findChild<QComboBox*>("boxModule");
	m_boxType = findChild<QComboBox*>("boxType");
	m_boxPri = findChild<QComboBox*>("boxPri");

    m_editStory = findChild<QLineEdit*>("editStory");
    m_textDesc = findChild<QTextEdit*>("textDesc");
    m_editTitle = findChild<QLineEdit*>("editTitle");
    m_texVerify = findChild<QTextEdit*>("texVerify");
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

void ZTDemand::SetupSignal()
{
    connect(m_boxProduct, SIGNAL(currentIndexChanged(int)), this, SLOT(OnProductChanged(int)));
}

void ZTDemand::OnProductChanged(int index)
{
    m_boxModule->clear();

    uint32_t product_id = static_cast<uint32_t>(m_boxProduct->itemData(index).toInt());
    emit ProductChanged(product_id, string_ptr(new std::string("story")));
}

void ZTDemand::OnDemandProductItems(zproduct_item_vec_ptr items)
{
    for (const auto& item : *items)
    {
        m_boxProduct->addItem(item.name_.c_str(), QVariant(item.id_));
    }
}

void ZTDemand::OnDemandModuleItems(zmodule_item_vec_ptr modules)
{
    for (const auto& item : *modules)
    {
        m_boxModule->addItem(item.name_.c_str(), QVariant(item.id_));
    }
}

void ZTDemand::OnDemandVersionItems(zversion_item_vec_ptr versions)
{
}


void ZTDemand::OnDemandPriItems(zpri_item_vec_ptr pris)
{
    for (const auto& item : *pris)
    {
        m_boxPri->addItem(item.name_.c_str(), QVariant(item.id_));
    }
}

void ZTDemand::OnDemandSeverityItems(zseverity_item_vec_ptr serveritys)
{
}

void ZTDemand::OnDemandOSItems(zos_item_vec_ptr oss)
{
}

void ZTDemand::OnDemandBrowserItems(zbrowser_item_vec_ptr browsers)
{
}

void ZTDemand::OnDemandTypeItems(ztype_item_vec_ptr types)
{
    for (const auto& item : *types)
    {
        m_boxType->addItem(item.name_.c_str(), QVariant(item.id_.c_str()));
    }
}

void ZTDemand::hideEvent(QHideEvent* event)
{
    QWidget::hideEvent(event);

    m_boxProduct->clear();
    m_boxModule->clear();
    m_boxPri->clear();
    m_boxType->clear();

    m_editStory->clear();
    m_textDesc->clear();
    m_editTitle->clear();
    m_texVerify->clear();
}

void ZTDemand::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}

#endif // NZENTAO_VER_
