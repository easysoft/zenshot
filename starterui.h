#pragma once

#define IS_TEST_VER 1

#include <QWidget>
#if IS_TEST_VER
#include <QPushButton>
#endif // IS_TEST_VER

class StarterUI : public QWidget {
	Q_OBJECT
public:
	StarterUI();
	virtual ~StarterUI();
signals:
	void SatrtShot();

private slots:
	void OnStartShot();

#if IS_TEST_VER
private:
	QPushButton m_startShot;
#endif // IS_TEST_VER
}; // StarterUI
