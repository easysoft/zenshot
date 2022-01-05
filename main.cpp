#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QMetaEnum>
#include <QFile>
#include <QList>
#include <QFontDatabase>

#include "widget.h"
#include "core/screeninfo.h"
#include "screen/helper/screengetter.h"
#include "starter.h"
#include "core/gparams.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //加载并应用语言翻译界面
    QLocale locale;
    QLocale::Language langEnum = locale.language();
    QMetaEnum metaEnum = QMetaEnum::fromType<QLocale::Language>();
    const char* langChar = metaEnum.valueToKey(langEnum);
    QString langName(langChar);

    QString langFile = ":/translations/" + langName + ".qm";
    if(QFile(langFile).exists() == false)
    {
        langFile = ":/translations/English.qm";
    }

    QTranslator translator;
    translator.load(langFile);
    a.installTranslator(&translator);

    //加载图标字体文件
    int fontId = QFontDatabase::addApplicationFont(":/iconfont.ttf");
    QString fontNmae = QFontDatabase::applicationFontFamilies(fontId).at(0);

    //设置系统默认字体
    QFont defaultFont("微软雅黑",9);
    a.setFont(defaultFont);



    //解析命令行参数
    int result = GParams::instance()->fromArgs(argc,argv);

    if(result != 0)
        return result;

    a.setQuitOnLastWindowClosed(true);

    Starter starter;
    starter.init();

    return a.exec();
}
