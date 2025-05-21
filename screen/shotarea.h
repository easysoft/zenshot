/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef CATCHER_H
#define CATCHER_H

#include <QRect>
#include <QPixmap>
#include <QScreen>
#include <QPainter>
#include <QWidget>
#include <QVector>

#include "core/screenlist.h"
#include "core/rectshape.h"
#include "screen/helper/screengetter.h"

/**
 * @class : ShotArea
 * @brief : 截图区域类定义
 * @note  : 提供屏幕，和截图区域相关功能
 */
class ShotArea: public RectShape
{
public:
    explicit ShotArea(Workspace *m_workspace);
    ~ShotArea();

    /**
     * @brief 获取屏幕的矩形区域
     * @return 返回矩形区域
     */
    QRect allBoundary();

    /**
     * @brief 获取屏幕的截图
     * @return 截图数据
     */
    QPixmap allPixmap() const;

    /**
     * @brief 获取截图矩形区域
     * @return 矩形区域
     */
    QRect areaBoundary();

    /**
     * @brief 获取截图区域是否已确认
     * @return
     */
    bool areaConfirmed();

    /**
     * @brief 开始捕获
     */
    void start(std::shared_ptr<ScreenList> list, int index);

    /**
     * @brief 清理状态
     */
    void cleanup();

    /**
     * @brief 自动捕获屏幕及窗口
     */
    void autoCapture();

    /**
     * @brief 确认截图区域
     */
    void confirmArea();

    /**
     * @brief 获取给定点命中的控制手柄
     * @param point 给定的点
     * @return 控制手柄
     */
    Handle* handleAt(QPoint point);

    /**
     * @brief 获取最终的截图结果
     * @return
     */
    QPixmap result();

    virtual QVector<Handle*> handles();
    void draw(QPainter &painter);


private:
    int m_nowScreenIndex;         //截图区域所在的屏幕
    QRect m_allScreenRect;        //截图区域所在屏幕的位置大小
    QPixmap m_maskPixmap;         //遮罩对应图像的数据
    std::shared_ptr<ScreenList> m_screenList;

    QVector<Handle*> m_handles;   //控制手柄列表

    bool m_areaConfirmed;         //是否选定了截图区域
    bool m_isGettingResult;       //是否真在获取结果

    QPen m_indicatorPen;          //边框画笔

    void autoCaptureWindow();     //自动捕获窗口

    void drawMagnifier(QPainter &painter);

protected:
    void loadPropsImpl(Store *store);
    void savePropsImpl(Store *store);
};

#endif // CATCHER_H
