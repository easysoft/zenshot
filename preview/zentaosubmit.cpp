#include "zentaosubmit.h"

#include "spdlogwrapper.hpp"
#include "config/xmlconfig.h"
#include "config/configvalue.h"

#include <QPainter>
#include <QFile>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QStandardItemModel>

#if !NZENTAO_VER_
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

    m_btnDemand = findChild<QPushButton*>("btnDemand");
    m_btnBug = findChild<QPushButton*>("btnBug");
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
	connect(m_btnDemand, SIGNAL(clicked()), this, SIGNAL(SubmitDemand()));
	connect(m_btnBug, SIGNAL(clicked()), this, SIGNAL(SubmitBug()));
    connect(this, SIGNAL(SubmitDemand()), this, SLOT(OnBtnSumitDemand()));
    connect(this, SIGNAL(SubmitBug()), this, SLOT(OnBtnSubmitBug()));

	connect(this, SIGNAL(RealSubmitDemand()), this, SIGNAL(UploadImage()));
	connect(this, SIGNAL(RealSubmitBug()), this, SIGNAL(UploadImage()));

	connect(this, SIGNAL(ShowThumbnail(std::shared_ptr<QPixmap>)), m_Preview, SLOT(OnShowThumbnail(std::shared_ptr<QPixmap>)));
    connect(m_Demand, SIGNAL(ProductChanged(uint32_t, string_ptr)), this, SIGNAL(SubmitReqModule(uint32_t, string_ptr)));
    connect(m_Bug, SIGNAL(ProductChanged(uint32_t, string_ptr)), this, SIGNAL(SubmitReqModule(uint32_t, string_ptr)));
    connect(m_Bug, SIGNAL(ProductChanged(uint32_t, string_ptr)), this, SIGNAL(SubmitReqVersion(uint32_t, string_ptr)));

#define connect_act_ack(act__, type__) \
    connect(this, SIGNAL(Demand##act__##Items(type__)), m_Demand, SLOT(OnDemand##act__##Items(type__))); \
    connect(this, SIGNAL(Bug##act__##Items(type__)), m_Bug, SLOT(OnBug##act__##Items(type__)));

    connect_act_ack(Product, zproduct_item_vec_ptr);
    connect_act_ack(Module, zmodule_item_vec_ptr);
    connect_act_ack(Version, zversion_item_vec_ptr);
    connect_act_ack(Pri, zpri_item_vec_ptr);
    connect_act_ack(Severity, zseverity_item_vec_ptr);
    connect_act_ack(OS, zos_item_vec_ptr);
    connect_act_ack(Browser, zbrowser_item_vec_ptr);
    connect_act_ack(Type, ztype_item_vec_ptr);

//     connect(this, SIGNAL(DemandProductItems(zproduct_item_vec_ptr)), m_Demand, SLOT(OnDemandProductItems(zproduct_item_vec_ptr)));
//     connect(this, SIGNAL(BugProductItems(zproduct_item_vec_ptr)), m_Bug, SLOT(OnBugProductItems(zproduct_item_vec_ptr)));

#undef connect_act_ack
}

void ZTSubmitDlg::OnSubmitDemand()
{
	m_Index = IDX_DEMAND;
}

void ZTSubmitDlg::OnSubmitBug()
{
	m_Index = IDX_BUG;
}

void ZTSubmitDlg::OnBtnSumitDemand()
{
    m_Index = IDX_DEMAND;
	auto name = m_Preview->GetCurrentSite();
	if (name.empty())
		return;

	m_framesWidget->setEnabled(false);
	emit SubmitLogin(string_ptr(new std::string(name)));
}

void ZTSubmitDlg::OnBtnSubmitBug()
{
    m_Index = IDX_BUG;
	auto name = m_Preview->GetCurrentSite();
	if (name.empty())
		return;

	m_framesWidget->setEnabled(false);
	emit SubmitLogin(string_ptr(new std::string(name)));
}

void ZTSubmitDlg::OnNextStep()
{
	int index = m_framesWidget->currentIndex();
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
	m_btnNext->hide();

	m_btnDemand->show();
	m_btnBug->show();
}

void ZTSubmitDlg::OnSubmitLoginResult(bool result)
{
    m_framesWidget->setEnabled(true);

    if (!result)
        return;

    m_btnNext->setText(tr("submit2zentao"));
    m_framesWidget->setCurrentIndex(m_Index);

    m_btnCancel->show();
    m_btnNext->show();

    m_btnDemand->hide();
    m_btnBug->hide();

    emit SubmitReqProduct();
    if (m_Index == IDX_DEMAND)
    {
        emit SubmitReqModules(string_ptr(new std::string("story")));
    }
    else
    {
        emit SubmitReqModules(string_ptr(new std::string("bug")));
    }
    
}

void ZTSubmitDlg::OnSubmitProductItems(zproduct_item_vec_ptr products)
{
    if (m_Index == IDX_DEMAND)
    {
        emit DemandProductItems(products);
    }
    else
    {
        emit BugProductItems(products);
    }
}

void ZTSubmitDlg::OnSubmitModuleItems(zmodule_item_vec_ptr modules)
{
    if (m_Index == IDX_DEMAND)
    {
        emit DemandModuleItems(modules);
    }
    else
    {
        emit BugModuleItems(modules);
    }
}

void ZTSubmitDlg::OnSubmitVersionItems(zversion_item_vec_ptr versions)
{
    if (m_Index == IDX_DEMAND)
    {
        emit DemandVersionItems(versions);
    }
    else
    {
        emit BugVersionItems(versions);
    }
}

void ZTSubmitDlg::OnSubmitModulesItems(zpri_item_vec_ptr pris, zseverity_item_vec_ptr serveritys, zos_item_vec_ptr oss, zbrowser_item_vec_ptr browers, ztype_item_vec_ptr types)
{
    if (m_Index == IDX_DEMAND)
    {
        emit DemandPriItems(pris);
        emit DemandTypeItems(types); 
    }
    else
    {
        emit BugPriItems(pris);
        emit BugSeverityItems(serveritys);
        emit BugOSItems(oss);
        emit BugBrowserItems(browers);
        emit BugTypeItems(types);
    }
}

void ZTSubmitDlg::OnUploadImageDone(bool success, string_ptr url)
{
    if (m_Index == IDX_DEMAND)
    {
        string_ptr json(new std::string);
        uint32_t product_id = m_Demand->BuildDemandJson(success ? *url : "", json);
        if (json->empty())
        {
            return;
        }

        emit SubmitDemandJson(product_id, json);
    }
    else
    {
        string_ptr json(new std::string);
        uint32_t product_id = m_Bug->BuildBugJson(success ? *url : "", json);
        if (json->empty())
        {
            return;
        }

        emit SubmitBugJson(product_id, json);
    }
}

void ZTSubmitDlg::showEvent(QShowEvent* event)
{
	QDialog::showEvent(event);

	m_Index = IDX_DEMAND;
	m_framesWidget->setCurrentIndex(IDX_PREVIEW);
    m_framesWidget->setEnabled(true);
	
    m_btnCancel->hide();
    m_btnNext->hide();

    m_btnDemand->show();
    m_btnBug->show();
}

void ZTSubmitDlg::hideEvent(QHideEvent* event)
{
	QDialog::hideEvent(event);

	m_Index = IDX_PREVIEW;
	m_btnCancel->hide();
	m_btnNext->hide();

	m_btnDemand->hide();
	m_btnBug->hide();

    emit SubmitZentaoHide();
}

void ZTSubmitDlg::closeEvent(QCloseEvent* event)
{
	event->ignore();
	hide();
}

#endif // NZENTAO_VER_
