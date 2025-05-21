/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef SCREENLIST_H
#define SCREENLIST_H

#include <QPainter>
#include <QRect>

#include "core/screeninfo.h"

#include <memory>

/**
 * @class : ScreenList
 * @brief : 屏幕列表集合
 * @note  : 屏幕列表集合基本功能
 */
class ScreenList
{
public:
    ScreenList(QList<ScreenInfo> list);

    QRect allBoundary(bool isGlobal=false) const;
    QPixmap allPixMap() const;

    QRect boundaryAt(int screenIndex,bool isGlobal=false);
    QScreen *screenAt(int screenIndex);
    QPixmap pixmapAt(int screenIndex);

    QRect toLocal(QRect rect);
    float scale();

    void draw(QPainter &painter);
    void draw(QPainter &painter,QPainterPath maskPath,QBrush maskBrush);

private:
    QRect m_allBoundary;
    std::shared_ptr<QPixmap> m_allPixMap;
    QList<ScreenInfo> m_List;

    void initParams();
};

#endif // SCREENLIST_H
