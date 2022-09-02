#include "zentaosubmit.h"

#include "spdlogwrapper.hpp"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

extern std::string SETTING_XML_NAME;

static int IDX_PREVIEW = 0;
static int IDX_DEMAND = 0;
static int IDX_BUG = 0;

ZTSubmitDlg::ZTSubmitDlg(QWidget* parent)
	: QDialog(parent)
	, m_Index(IDX_PREVIEW)
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

	m_Preview = new ZTPreview(nullptr);
	m_Demand = new ZTDemand(nullptr);
	m_Bug = new ZTBug(nullptr);

	IDX_PREVIEW = m_framesWidget->addWidget(m_Preview);
	IDX_DEMAND = m_framesWidget->addWidget(m_Demand);
	IDX_BUG = m_framesWidget->addWidget(m_Bug);

	m_framesWidget->setCurrentIndex(IDX_PREVIEW);
	m_Index = IDX_PREVIEW;

	m_btnNext = findChild<QPushButton*>("btnNext");
	m_btnCancel = findChild<QPushButton*>("btnCancel");
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
	connect(m_btnNext, SIGNAL(clicked()), this, SLOT(OnNextStep()));
	connect(m_btnCancel, SIGNAL(clicked()), this, SLOT(OnCancel()));

	connect(m_Preview, SIGNAL(SubmitDemand()), this, SLOT(OnSubmitDemand()));
	connect(m_Preview, SIGNAL(SubmitBug()), this, SLOT(OnSubmitBug()));

	connect(this, SIGNAL(RealSubmitDemand()), this, SLOT(OnRealSubmitDemand()));
	connect(this, SIGNAL(RealSubmitBug()), this, SLOT(OnRealSubmitBug()));

	connect(this, SIGNAL(ShowThumbnail(std::shared_ptr<QPixmap>)), m_Preview, SLOT(OnShowThumbnail(std::shared_ptr<QPixmap>)));
}

void ZTSubmitDlg::OnSubmitDemand()
{
	m_Index = IDX_DEMAND;
}

void ZTSubmitDlg::OnSubmitBug()
{
	m_Index = IDX_BUG;
}

void ZTSubmitDlg::OnNextStep()
{
	if (m_Index == IDX_PREVIEW)
	{
		return;
	}

	int index = m_framesWidget->currentIndex();
	if (index == IDX_PREVIEW)
	{
		m_btnNext->setText(tr("submit2zentao"));
		m_framesWidget->setCurrentIndex(m_Index);
		m_btnCancel->show();
		return;
	}

	if (index == IDX_DEMAND)
	{
		emit RealSubmitDemand();
		return;
	}
	if (index == IDX_BUG)
	{
		emit RealSubmitBug();
		return;
	}
}

void ZTSubmitDlg::OnCancel()
{
	m_btnNext->setText(tr("nextstep"));
	m_framesWidget->setCurrentIndex(IDX_PREVIEW);
	m_btnCancel->hide();
}

void ZTSubmitDlg::OnRealSubmitDemand()
{
}

void ZTSubmitDlg::OnRealSubmitBug()
{
}

void ZTSubmitDlg::showEvent(QShowEvent* event)
{
	QDialog::showEvent(event);

	m_Index = IDX_DEMAND;
	m_btnNext->setText(tr("nextstep"));
	m_framesWidget->setCurrentIndex(IDX_PREVIEW);
	m_btnCancel->hide();
}

void ZTSubmitDlg::hideEvent(QHideEvent* event)
{
	QDialog::hideEvent(event);

	m_Index = IDX_PREVIEW;
	m_btnCancel->hide();
}

void ZTSubmitDlg::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}
