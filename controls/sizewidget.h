#ifndef SIZEWIDGET_H
#define SIZEWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QVector>
#include <QColor>

#include "controls/sizebutton.h"

/**
 * @class : SizeWidget
 * @brief : 尺寸选择面板定义
 * @note  : 用来选择尺寸大小
 */
class SizeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SizeWidget(QWidget *parent = nullptr);

    int value() const;
    void setValue(int value);

    void setValueList(const QVector<int> &valueList);

private:
    QColor m_color;
    QVector<int> m_valueList;
    QVector<int> m_radiusList;

    int m_hGap;
    int m_itemLength;

    QVector<SizeButton*> m_btnList;

    int m_value;

    void initParams();
    void createUI();
    void initChecked();

signals:
    void sizeChanged();

private slots:
    void onItemClick(int index);

};

#endif // SIZEWIDGET_H
