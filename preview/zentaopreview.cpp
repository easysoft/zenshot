#include "zentaopreview.h"

#include "spdlogwrapper.hpp"
#include "config/xmlconfig.h"
#include "config/configvalue.h"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QStringListModel>

#if !NZENTAO_VER_
extern std::string SETTING_XML_NAME;

ZTPreview::ZTPreview(QWidget* parent)
	: QWidget(parent)
	, m_BtnGroup(this)
	, m_listModel(new QStringListModel(this))
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::Tool);

	SetupUI();
	SetupSignal();
}

std::string ZTPreview::GetCurrentSite()
{
    auto index = m_listView->currentIndex();
    if (index.row() == -1)
        return "";

    return index.data().toString().toUtf8().toStdString();
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

	m_listView = findChild<QListView*>("listView");
	m_listView->setModel(m_listModel);

	m_btnDemand = findChild<QPushButton*>("btnDemand");
	m_btnBug = findChild<QPushButton*>("btnBug");

	m_BtnGroup.addButton(m_btnDemand, 0);
	m_BtnGroup.addButton(m_btnBug, 1);

	m_BtnGroup.setExclusive(true);

	m_imgview = findChild<QLabel*>("imgview");
}

void ZTPreview::SetupSignal()
{
	connect(m_btnDemand, SIGNAL(clicked()), this, SIGNAL(SubmitDemand()));
	connect(m_btnBug, SIGNAL(clicked()), this, SIGNAL(SubmitBug()));
}

void ZTPreview::showEvent(QShowEvent* event)
{
	QWidget::showEvent(event);

	QStringList names;
	auto cb = [&](rapidxml::xml_node<>* root, rapidxml::xml_node<>* node)
	{
		(void*)root;
		auto name_attr = node->first_attribute("name");
		auto name = name_attr->value();
		names.append(name);
		return false;
	};
	GetXMLConfig().FindAllNode("config", "zentao", cb);

	m_listModel->setStringList(names);
	
	m_btnDemand->setChecked(true);
	emit SubmitDemand();
}

void ZTPreview::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}

void ZTPreview::OnShowThumbnail(std::shared_ptr<QPixmap> pixmap)
{
	pixmap->scaled(m_imgview->size(), Qt::KeepAspectRatio);
	m_imgview->setPixmap(*pixmap);
}

#endif // NZENTAO_VER_
