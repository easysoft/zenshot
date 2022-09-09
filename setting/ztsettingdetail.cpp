#include "ztsettingdetail.h"
#include "spdlogwrapper.hpp"

#include "config/xmlconfig.h"
#include "config/configvalue.h"

#include <QFile>
#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>

extern std::string SETTING_XML_NAME;

#if !NZENTAO_VER_
ZTSettingDetail::ZTSettingDetail(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint);

	InitUI();
	SetupUI();
	SetupSignal();

	m_textPass->installEventFilter(this);
}

bool ZTSettingDetail::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::FocusOut)
	{
		if (watched == m_textPass)
		{
			emit CheckInputDone();
		}
	}

	return QWidget::eventFilter(watched, event);
}

void ZTSettingDetail::OnChangeCurrentSelectDetail(int index, string_ptr name, string_ptr url, string_ptr usr, string_ptr pass)
{
	if (index == -1)
	{
		m_textName->setText("");
		m_textUri->setText("");
		m_textUsr->setText("");
		m_textPass->setText("");
	}
	else
	{
		m_textName->setText(name->c_str());
		m_textUri->setText(url->c_str());
		m_textUsr->setText(usr->c_str());
		m_textPass->setText(pass->c_str());
	}

	m_checkSetDefault->blockSignals(true);
	m_checkSetDefault->setChecked(name && m_DefaultSite == *name);
	m_checkSetDefault->blockSignals(false);
}

void ZTSettingDetail::OnStateChanged(int state)
{
	if (state == Qt::Checked)
	{
		m_DefaultSite = GetName();

		emit SetDefaultSite(true);
	}
	else
	{
		m_DefaultSite = "";
		emit SetDefaultSite(false);
	}
}

void ZTSettingDetail::OnSaveDefaultSite()
{
	bool done = false;
	auto cb = [&](rapidxml::xml_node<>*& root, rapidxml::xml_node<>*& node)
	{
		(void*)root;

		SetConfigStr(node, nullptr, m_DefaultSite.c_str());

		done = true;
		return true;
	};
	GetXMLConfig().FindAllNode("config", "default", cb);

	if (!done)
	{
		GetXMLConfig().AddConfigString2("config", "default", m_DefaultSite.c_str());
	}
	
	GetXMLConfig().SaveConfig(SETTING_XML_NAME);
}

void ZTSettingDetail::showEvent(QShowEvent* event)
{
	QWidget::showEvent(event);

	auto cb = [&](rapidxml::xml_node<>*& root, rapidxml::xml_node<>*& node)
	{
		(void*)root;

		m_DefaultSite = GetConfigString(node);

		return true;
	};
	GetXMLConfig().FindAllNode("config", "default", cb);
}

void ZTSettingDetail::InitUI()
{
	m_checkSetDefault = findChild<QCheckBox*>("checkSetDefault");
	
	m_labelNameTitle = findChild<QLabel*>("labelNameTitle");
	m_labelUriTitle = findChild<QLabel*>("labelUriTitle");
	m_labelUsr = findChild<QLabel*>("labelUsr");
	m_labelPass = findChild<QLabel*>("labelPass");

	m_btnSave = findChild<QPushButton*>("btnSave");
	m_btnNew = findChild<QPushButton*>("btnNew");

	m_textName = findChild<QLineEdit*>("textName");
	m_textUri = findChild<QLineEdit*>("textUri");
	m_textUsr = findChild<QLineEdit*>("textUsr");
	m_textPass = findChild<QLineEdit*>("textPass");
}

void ZTSettingDetail::SetupUI()
{
	// load qss
	QFile file(":/zentaosettingdetail.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);
}

void ZTSettingDetail::SetupSignal()
{
	connect(m_checkSetDefault, SIGNAL(stateChanged(int)), this, SLOT(OnStateChanged(int)));
	connect(this, SIGNAL(SaveDefaultSite()), this, SLOT(OnSaveDefaultSite()));

	connect(m_btnSave, SIGNAL(clicked()), this, SIGNAL(ConfigSave()));
	connect(m_btnNew, SIGNAL(clicked()), this, SIGNAL(ConfigNew()));

	connect(this, SIGNAL(ChangeCurrentSelectDetail(int, string_ptr, string_ptr, string_ptr, string_ptr)), this, SLOT(OnChangeCurrentSelectDetail(int, string_ptr, string_ptr, string_ptr, string_ptr)));

	connect(m_textName, SIGNAL(textChanged(const QString&)), this, SIGNAL(UpdateName(const QString&)));
	connect(m_textUri, SIGNAL(textChanged(const QString&)), this, SIGNAL(UpdateUrl(const QString&)));
	connect(m_textUsr, SIGNAL(textChanged(const QString&)), this, SIGNAL(UpdateUsr(const QString&)));
	connect(m_textPass, SIGNAL(textChanged(const QString&)), this, SIGNAL(UpdatePass(const QString&)));
}

#endif // NZENTAO_VER_
