QT       += core gui

RC_FILE += zenshot.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++11
QMAKE_CXXFLAGS_RELEASE += -O2

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commands/addcommand.cpp \
    commands/deletecommand.cpp \
    commands/locatorcommand.cpp \
    commands/movecommand.cpp \
    commands/propscommand.cpp \
    commands/textcontentcommand.cpp \
    config/xmlconfig.cpp \
    controls/colorbutton.cpp \
    controls/colorwidget.cpp \
    controls/pencombobox.cpp \
    controls/penitemwidget.cpp \
    controls/penrenderer.cpp \
    controls/sizebutton.cpp \
    controls/sizeinputwidget.cpp \
    controls/sizewidget.cpp \
    controls/textwidget.cpp \
    controls/textwidgetimpl.cpp \
    core/command.cpp \
    core/gparams.cpp \
    core/gscale.cpp \
    core/handle.cpp \
    core/locator.cpp \
    core/pointshape.cpp \
    core/propsbar.cpp \
    core/rectshape.cpp \
    core/screenlist.cpp \
    core/shape.cpp \
    core/store.cpp \
    core/tool.cpp \
    core/useroper.cpp \
    core/utils.cpp \
    handles/rectshapehandle.cpp \
    locators/pointlocator.cpp \
    locators/rectlocator.cpp \
    main.cpp \
    preview/zentaobug.cpp \
    preview/zentaodemand.cpp \
    preview/zentaopreview.cpp \
    preview/zentaosubmit.cpp \
    properties/arrowbar.cpp \
    properties/curvebar.cpp \
    properties/ellipsebar.cpp \
    properties/linebar.cpp \
    properties/mosaicbar.cpp \
    properties/rectanglebar.cpp \
    properties/textbar.cpp \
    screen/handletool.cpp \
    screen/hovertool.cpp \
    screen/movetool.cpp \
    screen/shotarea.cpp \
    screen/shotarea/areacreatetool.cpp \
    screen/shotarea/areahandle.cpp \
    screen/shotarea/areahandletool.cpp \
    screen/shotarea/arealocator.cpp \
    screen/shotarea/areamovetool.cpp \
    screen/textassist.cpp \
    screen/toolbar.cpp \
    screen/workspace.cpp \
    setting/settingdlg.cpp \
    setting/zentaosetting.cpp \
    setting/ztsettingdetail.cpp \
    setting/ztsettinglist.cpp \
    setting/ztsettinglistitem.cpp \
    shapes/arrow.cpp \
    shapes/curve.cpp \
    shapes/ellipse.cpp \
    shapes/line.cpp \
    shapes/mosaic.cpp \
    shapes/rectangle.cpp \
    shapes/text.cpp \
    spdlogwrapper.cpp \
    starter.cpp \
    starterui.cpp \
    stores/localstore.cpp \
    stores/memorystore.cpp \
    tools/arrowcreatetool.cpp \
    tools/curvecreatetool.cpp \
    tools/ellipsecreatetool.cpp \
    tools/linecreatetool.cpp \
    tools/mosaiccreatetool.cpp \
    tools/rectcreatetool.cpp \
    tools/textcreatetool.cpp \
    httprequest/zhttprequest.cpp \
    widget.cpp \
    zentaologic.cpp

HEADERS += \
    commands/addcommand.h \
    commands/deletecommand.h \
    commands/locatorcommand.h \
    commands/movecommand.h \
    commands/propscommand.h \
    commands/textcontentcommand.h \
    config/configvalue.h \
    config/xmlconfig.h \
    controls/colorbutton.h \
    controls/colorwidget.h \
    controls/pencombobox.h \
    controls/penitemwidget.h \
    controls/penrenderer.h \
    controls/sizebutton.h \
    controls/sizeinputwidget.h \
    controls/sizewidget.h \
    controls/textwidget.h \
    controls/textwidgetimpl.h \
    core/command.h \
    core/gparams.h \
    core/gscale.h \
    core/handle.h \
    core/locator.h \
    core/pointshape.h \
    core/propsbar.h \
    core/rectshape.h \
    core/screeninfo.h \
    core/screenlist.h \
    core/shape.h \
    core/store.h \
    core/tool.h \
    core/useroper.h \
    core/utils.h \
    handles/rectshapehandle.h \
    locators/pointlocator.h \
    locators/rectlocator.h \
    preview/zentaobug.h \
    preview/zentaodemand.h \
    preview/zentaopreview.h \
    preview/zentaosubmit.h \
    properties/arrowbar.h \
    properties/curvebar.h \
    properties/ellipsebar.h \
    properties/linebar.h \
    properties/mosaicbar.h \
    properties/rectanglebar.h \
    properties/textbar.h \
    rapidxml/rapidxml.hpp \
    rapidxml/rapidxml_iterators.hpp \
    rapidxml/rapidxml_print.hpp \
    rapidxml/rapidxml_utils.hpp \
    screen/handletool.h \
    screen/helper/screengetter.h \
    screen/hovertool.h \
    screen/movetool.h \
    screen/shotarea.h \
    screen/shotarea/areacreatetool.h \
    screen/shotarea/areahandle.h \
    screen/shotarea/areahandletool.h \
    screen/shotarea/arealocator.h \
    screen/shotarea/areamovetool.h \
    screen/textassist.h \
    screen/toolbar.h \
    screen/workspace.h \
    setting/settingdlg.h \
    setting/zentaosetting.h \
    setting/ztsettingdetail.h \
    setting/ztsettinglist.h \
    setting/ztsettinglistitem.h \
    shapes/arrow.h \
    shapes/curve.h \
    shapes/ellipse.h \
    shapes/line.h \
    shapes/mosaic.h \
    shapes/rectangle.h \
    shapes/text.h \
    spdlogwrapper.hpp \
    starter.h \
    starterui.h \
    stores/localstore.h \
    stores/memorystore.h \
    tools/arrowcreatetool.h \
    tools/curvecreatetool.h \
    tools/ellipsecreatetool.h \
    tools/linecreatetool.h \
    tools/mosaiccreatetool.h \
    tools/rectcreatetool.h \
    tools/textcreatetool.h \
    httprequest/zhttprequest.h \
    usrmetatype.h \
    widget.h \
    zdata/zdataitem.h

TRANSLATIONS = translations/chinese.ts \
               translations/english.ts

unix:!macx {
    QT       += x11extras
    LIBS     += -lX11

    SOURCES += screen/helper/windowgetter_x11.cpp
    HEADERS += screen/helper/windowgetter.h

    SOURCES += screen/helper/screengetter_x11.cpp
}

win32 {
    RC_ICONS = zenshot.ico
    LIBS    += User32.lib
    
    SOURCES += screen/helper/windowgetter_win.cpp
    HEADERS += screen/helper/windowgetter.h

    SOURCES += screen/helper/screengetter_win.cpp
}

macx {
    OBJECTIVE_SOURCES += screen/helper/windowgetter_mac.mm
    OBJECTIVE_HEADERS += screen/helper/windowgetter.h

    SOURCES += screen/helper/screengetter_mac.cpp

    LIBS += -framework Cocoa
    LIBS += -framework CoreGraphics
    LIBS += -framework CoreFoundation
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    main.qrc

DISTFILES +=
DEFINES += NZENTAO_VER_

FORMS += \
    setting.ui \
    zentaobug.ui \
    zentaodemand.ui \
    zentaopreview.ui \
    zentaosetting.ui \
    zentaosetting.ui \
    zentaosettingdetail.ui \
    zentaosettinglist.ui \
    zentaosubmit.ui

