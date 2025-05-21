/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef TEXTWIDGETIMPL_H
#define TEXTWIDGETIMPL_H

#include <QTextEdit>
#include <QSize>

/**
 * @class : TextWidgetImpl
 * @brief : 文本编辑类定义
 * @note  : 高宽自动调整的文本编辑
 */
class TextWidgetImpl : public QTextEdit
{
    Q_OBJECT

public:
    explicit TextWidgetImpl(QWidget* parent = nullptr);

    QSize desireSize();
    void adjustSize();
    void setFont(const QFont& f);
    void setTextColor(const QColor& c);

protected:
    void showEvent(QShowEvent* e);
    void resizeEvent(QResizeEvent* e);

signals:
    void textUpdated(const QString& s);
    void sizeChanged(QSize size);

private slots:
    void emitTextUpdated();    
};

#endif // TEXTWIDGETIMPL_H
