#include "StarterUI.h"

#include "starter.h"

StarterUI::StarterUI()
	: QWidget(0)
#if IS_TEST_VER
	, m_startShot(this)
#endif // IS_TEST_VER
{
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
#if !IS_TEST_VER
	setAttribute(Qt::WA_TranslucentBackground, true);
#else
	m_startShot.setText(u8"start");
	connect(&m_startShot, SIGNAL(clicked()), this, SIGNAL(SatrtShot()));
#endif // IS_TEST_VER

	connect(this, SIGNAL(SatrtShot()), this, SLOT(OnStartShot()));
}

StarterUI::~StarterUI()
{
}

void StarterUI::OnStartShot()
{
	Starter starter;
	starter.init();
}
