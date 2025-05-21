/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef APPINSTALL_H
#define APPINSTALL_H

#include <QObject>

#include "widget.h"

class Starter
    : public QObject
{
    Q_OBJECT
public:
    Starter(bool exit_process);
    virtual ~Starter();

    void init(QWidget* parent = nullptr);
    void cleanup();

    void rasie();

private:
    QList<Widget*>* m_widgets;
    QList<Widget*>* m_unused_widgets;

signals:
    void ShotDone(Starter*);
    void ShotResult(std::shared_ptr<QPixmap> pixmap);

private slots:
    void finishShot(int code);
    void finishConfirmArea();

private:
    bool m_bExit;
};

#endif // APPINSTALL_H
