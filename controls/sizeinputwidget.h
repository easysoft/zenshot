/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef SIZEINPUTWIDGET_H
#define SIZEINPUTWIDGET_H

#include <QWidget>
#include <QSpinBox>

#include "core/gscale.h"

class SizeInputWidget : public QWidget,GScale
{
    Q_OBJECT
public:
    SizeInputWidget(QWidget *parent=nullptr);

    int value() const;
    void setValue(int value);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int m_minSize;
    int m_maxSize;

    QSpinBox *m_inpputBox;

signals:
    void sizeChanged();

private slots:
    void onInpputIntChanged(int);
};

#endif // SIZEINPUTWIDGET_H
