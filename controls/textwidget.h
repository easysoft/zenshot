/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QDialog>
#include <QHideEvent>

#include <memory>

#include "controls/textwidgetimpl.h"

class TextWidget : public QDialog
{
    Q_OBJECT
public:
    TextWidget(QWidget *parent=nullptr);

    QString text();
    void setText(QString text);

    void setFont(const QFont& f);
    void setTextColor(const QColor c);

    void makeFocus();

protected:
    void paintEvent(QPaintEvent *event);

private:
    TextWidgetImpl* m_textImpl;

private slots:
    void onContentSizeChanged(QSize size);
    void hideEvent(QHideEvent* event) override;

};

#endif // TEXTWIDGET_H
