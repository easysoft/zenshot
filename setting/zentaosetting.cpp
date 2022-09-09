#include "zentaosetting.h"

#include "ztsettingdetail.h"
#include "config/xmlconfig.h"
#include "config/configvalue.h"
#include "spdlogwrapper.hpp"
#include "starterui.h"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QMessageBox>

#if !NZENTAO_VER_
extern StarterUI* g_start_ui_;
extern std::string SETTING_XML_NAME;

ZTSettingDlg::ZTSettingDlg(QWidget* parent)
	: QDialog(parent)
    , m_Layout()
	, m_Detail(nullptr)
    , m_List(nullptr)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::Tool);

	SetupUI();
	SetupSignal();
}

void ZTSettingDlg::OnConfigCancel()
{
	hide();
}

void ZTSettingDlg::OnConfigSave()
{
	emit SaveZentaoSiteConfig();
	emit SaveZentaoDefaultSite();

	hide();
}

void ZTSettingDlg::OnCheckInputDone()
{
	string_ptr name(new std::string(m_Detail.GetName()));
	string_ptr url(new std::string(m_Detail.GetUrl()));
	string_ptr usr(new std::string(m_Detail.GetUsr()));
	string_ptr pass(new std::string(m_Detail.GetPass()));

	if (name->empty() || url->empty() || usr->empty() || pass->empty())
	{
		return;
	}

	QString err_msg;
	if (g_start_ui_->UsrLogin(url, usr, pass, err_msg))
	{
		if (err_msg.isEmpty())
		{
			QMessageBox::information(g_start_ui_, tr("Title"), tr("unknownerr"));
		}
		else
		{
			QMessageBox::information(g_start_ui_, tr("Title"), err_msg);
		}
		
	}
}

void ZTSettingDlg::SetupUI()
{
	// load qss
	QFile file(":/zentaosetting.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);

	setLayout(&m_Layout);
	m_Layout.setSpacing(0);
	m_Layout.setContentsMargins(40, 30, 40, 30);

	m_Layout.addWidget(&m_Detail, 54);
	m_Layout.addWidget(&m_List, 46);
}

void ZTSettingDlg::SetupSignal()
{
	connect(this, SIGNAL(ConfigCancel()), this, SLOT(OnConfigCancel()));
	connect(&m_Detail, SIGNAL(ConfigSave()), this, SLOT(OnConfigSave()));

	connect(&m_List, SIGNAL(CurrentRowSelected(int, string_ptr, string_ptr, string_ptr, string_ptr)), &m_Detail, SIGNAL(ChangeCurrentSelectDetail(int, string_ptr, string_ptr, string_ptr, string_ptr)));
	
	connect(this, SIGNAL(SaveZentaoSiteConfig()), &m_List, SIGNAL(SaveSiteListConfig()));
	connect(this, SIGNAL(SaveZentaoDefaultSite()), &m_Detail, SIGNAL(SaveDefaultSite()));

	connect(&m_Detail, SIGNAL(ConfigNew()), &m_List, SLOT(OnNewSiteConfig()));
	connect(&m_Detail, SIGNAL(CheckInputDone()), this, SLOT(OnCheckInputDone()));

	connect(&m_Detail, SIGNAL(UpdateName(const QString&)), &m_List, SLOT(OnUpdateName(const QString&)));
	connect(&m_Detail, SIGNAL(UpdateUrl(const QString&)), &m_List, SLOT(OnUpdateUrl(const QString&)));
	connect(&m_Detail, SIGNAL(UpdateUsr(const QString&)), &m_List, SLOT(OnUpdateUsr(const QString&)));
	connect(&m_Detail, SIGNAL(UpdatePass(const QString&)), &m_List, SLOT(OnUpdatePass(const QString&)));
	connect(&m_Detail, SIGNAL(SetDefaultSite(bool)), &m_List, SLOT(OnSetDefaultItem(bool)));
}

void ZTSettingDlg::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}

void ZTSettingDlg::hideEvent(QHideEvent* event)
{
	QDialog::hideEvent(event);

	emit SettingZentaoHide();
}

#endif // NZENTAO_VER_