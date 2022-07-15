#pragma once

#define IS_TEST_VER 1

#include "starter.h"

#include <QWidget>
#if IS_TEST_VER
#include <QPushButton>
#endif // IS_TEST_VER

#include <list>

class StarterUI : public QWidget {
	Q_OBJECT
public:
	StarterUI();
	virtual ~StarterUI();
signals:
	void SatrtShot();
	void ShotDone(Starter* starer);

private slots:
	void OnStartShot();
	void OnShotDone(Starter* starer);

protected:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
	virtual bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);
#else
	virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#endif

private:
#if IS_TEST_VER
	QPushButton m_startShot;
#endif // IS_TEST_VER
	std::list<Starter*> m_Starer;
}; // StarterUI
