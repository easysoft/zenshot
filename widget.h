/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <screen/workspace.h>
#include <QPixmap>
#include <QPainter>

#include "core/screenlist.h"

#include <memory>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void start(std::shared_ptr<ScreenList> list, int index);
    void cleanup();

    Workspace* workspace() const;
    void finishConfirmArea();

protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent *event) override;

private:
	QString m_status;  //unknown, active, giveup
	Workspace* m_workspace;
	std::shared_ptr<ScreenList> m_screenlist;
};

#endif // WIDGET_H
