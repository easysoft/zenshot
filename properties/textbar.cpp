#include "textbar.h"
#include "core/utils.h"

#include <QVariant>
#include <QListWidget>
#include <QFontDatabase>

TextBar::TextBar(Workspace *workspace) : PropsBar(workspace)
{
     createWidget();
     loadProps();
     connectEvents();
}

void TextBar::createWidget()
{
    //字号组件初始化
    m_sizeComboBox = new QComboBox();
    m_sizeComboBox->setMinimumWidth(45);

    QVector<int> sizeList = {10,12,14,16,18,20,24,28,32,40,48,56,64,72};
    foreach(int i,sizeList)
    {
        m_sizeComboBox->addItem(QString::number(i),i);
    }

    m_layout->addWidget(m_sizeComboBox);

    //添加分割线
    //addSeperator();

    //字体组件初始化
    QListWidget *fListWidget = new QListWidget(this);
    QFontDatabase fontData;
    foreach(QString strFont,fontData.families(QFontDatabase::SimplifiedChinese))
    {
        if(fontData.isSmoothlyScalable(strFont) == true)
        {
            QListWidgetItem *fItem = new QListWidgetItem(strFont,fListWidget);
            fItem->setFont(QFont(strFont));
            fListWidget->addItem(fItem);
        }
    }
    m_fontComboxBox = new QComboBox();
    m_fontComboxBox->setMaximumWidth(120);
    m_fontComboxBox->setModel(fListWidget->model());
    m_fontComboxBox->setView(fListWidget);
    m_layout->addWidget(m_fontComboxBox);

    //添加分割线
    //addSeperator();

    //字体颜色组件初始化
    m_colorWidget = new ColorWidget();
    m_layout->addWidget(m_colorWidget);

    //粗体
    m_boldCheckBox = new QCheckBox();
    m_boldCheckBox->setText(tr("bold"));
    m_layout->addWidget(m_boldCheckBox);

    //斜体
    m_italicCheckBox = new QCheckBox();
    m_italicCheckBox->setText(tr("italic"));
    m_layout->addWidget(m_italicCheckBox);

    //下划线
    m_underlineCheckBox = new QCheckBox();
    m_underlineCheckBox->setText(tr("underline"));
    m_layout->addWidget(m_underlineCheckBox);
}

void TextBar::loadProps()
{
    int mSize = m_store->read(Utils::forTextKey(),Utils::TextSizeName(),Utils::TextSizeDefault()).toInt();
    QColor mColor = m_store->readColor(Utils::forTextKey(),Utils::TextColorName(),Utils::TextColorDefault());
    QString mFamily = m_store->read(Utils::forTextKey(),Utils::TextFamilyName(),Utils::TextFamilyDefault()).toString();
    bool mBold = m_store->read(Utils::forTextKey(),Utils::TextBoldName(),Utils::TextBoldDefault()).toBool();
    bool mItalic = m_store->read(Utils::forTextKey(),Utils::TextItalicName(),Utils::TextItalicDefault()).toBool();
    bool mUnderline = m_store->read(Utils::forTextKey(),Utils::TextUnderlineName(),Utils::TextUnderlineDefault()).toBool();

    m_sizeComboBox->setCurrentText(QString::number(mSize));
    m_colorWidget->setSelectedColor(mColor);
    //m_familyComboBox->setCurrentText(mFamily);
    m_boldCheckBox->setChecked(mBold);
    m_italicCheckBox->setChecked(mItalic);
    m_underlineCheckBox->setChecked(mUnderline);

    m_fontComboxBox->setCurrentText(mFamily);

}

void TextBar::saveProps()
{
    QFont font = m_fontComboxBox->currentText();

    int mSize = m_sizeComboBox->currentData().toInt();
    QColor mColor = m_colorWidget->selectedColor();
    QString mFamily = font.family();
    bool mBold = m_boldCheckBox->isChecked();
    bool mItalic = m_italicCheckBox->isChecked();
    bool mUnderline = m_underlineCheckBox->isChecked();

    m_store->write(Utils::forTextKey(),Utils::TextSizeName(),mSize);
    m_store->writeColor(Utils::forTextKey(),Utils::TextColorName(),mColor);
    m_store->write(Utils::forTextKey(),Utils::TextFamilyName(),mFamily);
    m_store->write(Utils::forTextKey(),Utils::TextBoldName(),mBold);
    m_store->write(Utils::forTextKey(),Utils::TextItalicName(),mItalic);
    m_store->write(Utils::forTextKey(),Utils::TextUnderlineName(),mUnderline);

}

void TextBar::connectEvents()
{
    connect(m_sizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
    connect(m_colorWidget, SIGNAL(colorChanged()), this, SLOT(propsChanged()));
    //connect(m_familyComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
    connect(m_fontComboxBox, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
    connect(m_boldCheckBox, SIGNAL(stateChanged(int)), this, SLOT(indexChanged(int)));
    connect(m_italicCheckBox, SIGNAL(stateChanged(int)), this, SLOT(indexChanged(int)));
    connect(m_underlineCheckBox, SIGNAL(stateChanged(int)), this, SLOT(indexChanged(int)));
}

void TextBar::indexChanged(int index)
{
    propsChanged();
}
