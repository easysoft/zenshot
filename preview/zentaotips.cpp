#include "zentaotips.h"

#include "config/xmlconfig.h"
#include "config/configvalue.h"

#include <QCloseEvent>

ZTTipsDlg::ZTTipsDlg(QWidget* parent)
	: QDialog(parent)
	, m_3SecTimer(this)
	, m_Count(3)
{
	ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	m_3SecTimer.setInterval(1000);

	InitUI();
	SetupUI();
	SetupSignal();
}

void ZTTipsDlg::InitUI()
{
	m_labelSuccess = findChild<QLabel*>("labelSuccess");
	m_labelFailed = findChild<QLabel*>("labelFailed");
	m_labelMsg = findChild<QLabel*>("labelMsg");

	m_btnOkay = findChild<QPushButton*>("btnOkay");
	m_btnModify = findChild<QPushButton*>("btnModify");
	m_btn3Sec = findChild<QPushButton*>("btn3Sec");
}

void ZTTipsDlg::SetupUI()
{
	// load qss
	QFile file(":/zentaotips.css");

	file.open(QFile::ReadOnly);
	QString qss = QString::fromLatin1(file.readAll());
	file.close();

	// modif style
	setStyleSheet(qss);
}

void ZTTipsDlg::SetupSignal()
{
	connect(m_btnOkay, SIGNAL(clicked()), this, SLOT(hide()));
	connect(m_btnOkay, SIGNAL(clicked()), this, SIGNAL(OpenZentaoUrl()));
	connect(m_btnModify, SIGNAL(clicked()), this, SLOT(OnBtnModify()));
	connect(m_btnOkay, SIGNAL(clicked()), this, SLOT(hide()));

	connect(&m_3SecTimer, SIGNAL(timeout()), this, SLOT(OnUpdate3Sec()));
}

void ZTTipsDlg::SetContent(bool success, const QString& msg)
{
	m_btnOkay->setVisible(success);
	m_btnModify->setVisible(!success);
	m_btn3Sec->setVisible(success);

	m_labelSuccess->setVisible(success);
	m_labelFailed->setVisible(!success);

	m_labelMsg->setText(msg);

	if (success)
	{
		Update3SecTxt();
		m_3SecTimer.start();
	}
}

void ZTTipsDlg::showEvent(QShowEvent* event)
{
	QDialog::showEvent(event);

	setResult(Rejected);
}

void ZTTipsDlg::hideEvent(QHideEvent* event)
{
	QDialog::hideEvent(event);

	m_3SecTimer.stop();
	m_Count = 3;
}

void ZTTipsDlg::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}

void ZTTipsDlg::OnUpdate3Sec()
{
	m_Count--;

	Update3SecTxt();

	if (!m_Count)
	{
		hide();
	}
}

void ZTTipsDlg::OnBtnModify()
{
	setResult(Accepted);

	hide();
}

void ZTTipsDlg::Update3SecTxt()
{
	QString txt(QString::number(m_Count));
	txt += tr("close3sec");
	m_btn3Sec->setText(txt);
}
