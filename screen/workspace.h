/* Copyright (C) 2021 Nature Easy Soft Network Technology Co., LTD
 *
 * This file is part of Zenshot (https://github.com/easysoft/zenshot/).
 *
 * Zenshot is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zenshot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zenshot. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>
#include <QRect>
#include <QVector>
#include <QFont>
#include <QPushButton>

#include "screen/shotarea.h"
#include "core/tool.h"
#include "core/shape.h"
#include "screen/hovertool.h"
#include "screen/textassist.h"
#include "core/propsbar.h"
#include "screen/toolbar.h"
#include "core/screenlist.h"

/**
 * @class : Workspace
 * @brief : 截图入口类定义
 * @note  : 截图入口类定义
 */
class Workspace : public QObject
{
    Q_OBJECT

public:
    explicit Workspace(QWidget *m_widget);
    ~Workspace();

    /**
     * @brief 获取窗口组件
     * @return
     */
    QWidget* widget();

    /**
     * @brief 获取文本编辑辅助对象
     * @return
     */
    TextAssist *textAssist() const;

    /**
     * @brief 获取屏幕矩形区域
     * @return
     */
    QRect limitBoundary();

    /**
     * @brief 获取屏幕图像数据
     * @return 图像数据
     */
    QPixmap pixmap();

    /**
     * @brief 获取截图区域
     * @return
     */
    QRect areaBoundary();

    /**
     * @brief 设置截图区域
     * @param rect 矩形区域
     */
    void setAreaBoundary(QRect rect);

    /**
     * @brief 启动截屏
     */
    void start(ScreenList *list);

    /**
     * @brief 鼠标按下事件处理
     * @param event 事件参数
     */
    void onMousePress(QMouseEvent *event);

    /**
     * @brief 鼠标移动事件处理
     * @param event 事件参数
     */
    void onMouseMove(QMouseEvent *event);

    /**
     * @brief 鼠标释放事件处理
     * @param event 事件参数
     */
    void onMouseRelease(QMouseEvent *event);

    /**
     * @brief 键盘按键事件处理
     * @param event 事件参数
     */
    void onKeyPress(QKeyEvent *event);

    /**
     * @brief 自动捕获屏幕+窗口
     */
    void autoCapture();

    /**
     * @brief 移动截图区域
     * @param offsetPoint
     */
    void moveArea(QPoint offsetPoint);

    /**
     * @brief 确认截图区域
     */
    void confirmArea();

    /**
     * @brief 获取截图区域是否已确认
     * @return
     */
    bool areaConfirmed();

    /**
     * @brief 刷新图形绘制
     * @param isForce 是否立即强制绘制
     */
    void refreshDraw();

    /**
     * @brief 绘制图形
     * @param painter 绘图平面
     */
    void draw(QPainter &painter);

    /**
     * @brief 获取绘制图形数量
     * @return 图形数量
     */
    int shapeCount();

    /**
     * @brief 在给定位置获取图形控制手柄
     * @param point
     * @return
     */
    Handle* getShapeHandleAt(QPoint point);

    /**
     * @brief 在给定位置获取图形
     * @param point
     * @return
     */
    Shape* getShapeAt(QPoint point);

    /**
     * @brief 在给定位置获取截图区域控制手柄
     * @param point
     * @return
     */
    Handle* getShotAreaHandleAt(QPoint point);

    /**
     * @brief 判断在给定位置是否命中了截图区域
     * @param point
     * @return
     */
    bool isShotAreaSelfAt(QPoint point);

    /**
     * @brief 新增图形
     * @param shape 目标图形
     */
    void addShape(Shape *shape);

    /**
     * @brief 新增马赛克
     * @param shape 马赛克图形对象
     */
    void addMosaic(Shape *shape);

    /**
     * @brief 移除图形
     * @param shape 目标图形
     * @param tempOper 是否零时移除
     */
    void removeShape(Shape *shape,bool tempOper=false);

    /**
     * @brief 更新属性(仅更新当前选中的图形)
     */
    void refreshProps();

    /**
     * @brief 是否有图形创建工具
     * @return
     */
    bool hasCreateTool();

    /**
     * @brief 获取图形创建工具
     * @return
     */
    Tool *createTool() const;

    /**
     * @brief 重新定位工具属性面板
     */
    void rePositionBar();

    /**
     * @brief 设置选中图形
     * @param 被选中的图形
     */
    void setSelected(Shape *newSelected);

    /**
     * @brief 获取当前控制手柄
     * @return 控制手柄集合
     */
    QVector<Handle *> activeHandles() const;

    void normalbeforeUndo();


private:
    QFont m_iconfont;

    QWidget *m_widget;
    ShotArea m_shotArea;
    TextAssist *m_textAssist;

    Tool *m_tool;
    Tool *m_createTool;
    HoverTool *m_hoverTool;

    ToolBar *m_toolBar;
    PropsBar *m_propsBar;

    QPoint m_lastMosue;

    QVector<Shape*> m_shapeList;
    Shape* m_selectedShape;
    QVector<Handle*> m_activeHandles;

    bool m_firstRender;
    void loadResource();

    QPoint getMouse(QMouseEvent *event);

    void createToolBar();
    void createPropsBar();

    Tool* createCreateToolFactory(QString shapeType);
    PropsBar* createPropsBarFactory(QString shapeType);

    void deleteSelected();

    int saveClipboardImpl();
    int saveFolderImpl(QString folderPath);
    int saveImpl();
    void closeImpl(int code);

signals:
    void quitShot(int code);
    void finishConfirmArea();

private slots:
    void close();
    void save();
    void download();
    void createToolChanged(QString shapeType);
};

#endif // WORKSPACE_H
