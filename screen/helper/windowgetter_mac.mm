#include<QCursor>
#include<QScreen>
#include<QRect>
#include<QPoint>
#include<QWidget>

#import "screen/helper/windowgetter.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <CoreGraphics/CGWindow.h>
#import <CoreFoundation/CFArray.h>

struct WND_INFO{
    int id;   //winid
    int layer;//Z序
    int index;//序号
    QString title; //标题
    QRect pos;
};

QList<WND_INFO> GetWindowList()
{
    ProcessSerialNumber psn = { 0L, 0L };
    OSStatus err = GetFrontProcess(&psn);
    CFStringRef processName = NULL;
    err = CopyProcessName(&psn, &processName);
    NSString *pname = (NSString *)processName;

    QList<WND_INFO> list;
    CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly | kCGWindowListExcludeDesktopElements , kCGNullWindowID);
    CFIndex cnt = CFArrayGetCount(windowList);
    for (CFIndex i = 0; i < cnt ; i++)
    {
        NSDictionary *dict = (NSDictionary* )CFArrayGetValueAtIndex(windowList , i);

        NSString* ownerName = [dict objectForKey:(id)kCGWindowOwnerName];
        if([ownerName isEqualToString:pname])
            continue;


        CFStringRef stringRef = (__bridge CFStringRef) dict[@"kCGWindowName"];
        QString selfName = QString::fromCFString(stringRef);


        int layer = 0;
        CFNumberRef numberRef = (__bridge CFNumberRef) dict[@"kCGWindowLayer"];
        CFNumberGetValue(numberRef , kCFNumberSInt32Type , &layer);
        if(layer != 0)
            continue;

        CGRect windowRect;
        CGRectMakeWithDictionaryRepresentation((__bridge CFDictionaryRef)(dict[@"kCGWindowBounds"]) , &windowRect);

        QRectF pos;
        pos.setRect(windowRect.origin.x , windowRect.origin.y , windowRect.size.width , windowRect.size.height);

        int winId = 0;
        CFNumberRef wndIdRef = (__bridge CFNumberRef) dict[@"kCGWindowNumber"];
        CFNumberGetValue(wndIdRef , kCFNumberSInt32Type , &winId);

        WND_INFO info;
        info.id = winId;
        info.title = selfName;
        info.layer = layer;
        info.pos.setRect(pos.x() , pos.y() , pos.width() , pos.height());
        info.index = i;

        list.push_back(info);
    }

    return list;
}

static QList<WND_INFO> windowList;

QRect WindowGetter::winGeometry(QScreen *screen,QWidget *host)
{
    if(windowList.count() == 0)
        windowList = GetWindowList();

    QPoint mouse = QCursor::pos();

    for(WND_INFO info:windowList)
    {
        if(info.pos.contains(mouse))
            return info.pos;
    }

    return screen->geometry();
}

