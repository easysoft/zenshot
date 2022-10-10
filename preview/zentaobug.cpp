#include "zentaobug.h"

#include "spdlogwrapper.hpp"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

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

uint32_t ZTBug::BuildBugJson(const std::string& img, string_ptr json)
{
    /*
    {
        "title": "Bug2",
        "severity": 1,
        "pri": 1,
        "steps": "",
        "type": "codeerror",
        "openedBuild": [
            "trunk"
        ]
    }
    */

    int product_id = m_boxProduct->currentData().toInt();
    int module_id = m_boxModule->currentData().toInt();
    QString version_id = m_boxVersion->currentData().toString();
    int pri_id = m_cbxPri->currentData().toInt();
    int severity_id = m_cbxSeverity->currentData().toInt();
    QString os_id = m_cbxOS->currentData().toString();
    QString browser_id = m_cbxBrower->currentData().toString();
    QString type_id = m_cbxType->currentData().toString();
    auto date = m_TimeEditDeadLine->date();
    int year = date.year(),
        mm = date.month(),
        dd = date.day();

    QString deadline = QString::number(year) + "-" + QString::number(mm) + "-" + QString::number(dd);

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

    desc.replace("\r\n", "<br>");
    desc.replace("\n", "<br>");

    QJsonObject obj;
    obj.insert("module", module_id);
    obj.insert("title", title);
    obj.insert("severity", severity_id);
    obj.insert("pri", pri_id);
    obj.insert("type", type_id);
    obj.insert("os", os_id);
    obj.insert("browser", browser_id);
    obj.insert("steps", desc);
    obj.insert("deadline", deadline);

    if (version_id.isEmpty())
    {
        version_id = "trunk";
    }
    QJsonArray openedBuild;
    openedBuild.insert(0, version_id);
    obj.insert("openedBuild", openedBuild);

    QJsonDocument doc;
    doc.setObject(obj);
    *json = doc.toJson(QJsonDocument::Compact).toStdString();

    L_TRACE(json->c_str());

    return product_id;
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

    m_TimeEditDeadLine->setDisplayFormat("yyyy-MM-dd");
    m_TimeEditDeadLine->setDate(QDate::currentDate());

    QLineEdit* lEdit = m_TimeEditDeadLine->findChild<QLineEdit*>();
    if (lEdit)
    {
        lEdit->setReadOnly(true);
    }
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
        m_boxVersion->addItem(item.name_.c_str(), QVariant(item.id_.c_str()));
    }

    if (versions->empty())
    {
        m_boxVersion->addItem(tr("trunk"), "trunk");
    }
}

void ZTBug::OnBugPriItems(zpri_item_vec_ptr pris)
{
    QString index3_txt = "";
    for (const auto& item : *pris)
    {
		if (item.id_ == 3)
		{
			index3_txt = item.name_.c_str();
		}

        m_cbxPri->addItem(item.name_.c_str(), QVariant(item.id_));
    }

	if (!index3_txt.isEmpty())
	{
        m_cbxPri->setCurrentText(index3_txt);
	}
}

void ZTBug::OnBugSeverityItems(zseverity_item_vec_ptr serveritys)
{
    QString index3_txt = "";
    for (const auto& item : *serveritys)
    {
		if (item.id_ == 3)
		{
			index3_txt = item.name_.c_str();
		}

        m_cbxSeverity->addItem(item.name_.c_str(), QVariant(item.id_));
    }
	if (!index3_txt.isEmpty())
	{
        m_cbxSeverity->setCurrentText(index3_txt);
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

    resize(0, 0);

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
