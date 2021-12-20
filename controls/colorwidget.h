#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QVector>
#include <QColor>

#include "controls/colorbutton.h"

/**
 * @class : ColorWidget
 * @brief : 颜色选择面板定义
 * @note  : 用来选择颜色
 */
class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = nullptr);

    QColor selectedColor() const;
    void setSelectedColor(const QColor &selectedColor);

private:
    int m_maxColorNum;
    QColor m_selectedColor;
    QVector<QColor> m_colorList;

    int m_hGap;
    int m_vGap;
    int m_mainGap;

    int m_itemLength;
    int m_itemPadding;
    int m_itemActivePadding;

    int m_itemBorderWidth;
    int m_itemBorderRadius;
    QColor m_itemBorderColor;
    QColor m_itemBackgroundColor;

    ColorButton *m_selectedBtn;

    void initParams();
    void createUI();
    void setProps(ColorButton *btn,int length,int padding,int activePadding,QColor cotentColor,int radius);

private slots:
    void itemChanged(int newColorIndex);

signals:
    void colorChanged();
};

#endif // COLORWIDGET_H
