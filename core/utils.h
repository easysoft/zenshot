#ifndef SNAPCONST_H
#define SNAPCONST_H

#include <QColor>
#include <QPointF>
#include <QtMath>

/**
 * @class : Utils
 * @brief : 辅助功能定义
 * @note  : 涉及到的常量，默认值之类的定义
 */
class Utils
{
public:
    static int Handle_Area_Size;                //方形控制手柄的大小
    static int Handle_Area_Border_Thickness;    //方向控制手柄线宽
    static QColor Handle_Area_Border_Color;       //方形控制手柄线的颜色
    static QColor Handle_Area_Fill_Color;         //方形控制手柄填充颜色

    static int Handle_Shape_Size;             //园形控制手柄的大小
    static int Handle_Shape_Border_Thickness; //园向控制手柄线宽
    static QColor Handle_Shape_Border_Color;
    static QColor Handle_Shape_Fill_Color;      //园形控制手柄填充颜色

    static QColor Handle_AntLine_Color;       //蚂蚁线的颜色
    static QColor Handle_AntLine_SubColor;    //蚂蚁线的次级颜色
    static int Handle_AntLine_Thicknes;     //蚂蚁线的线宽

    static int Undo_Max_Count;                 //撤销重做支持的最大步数

    static int Hit_Snap;                    //鼠标拾取时的吸附距离

    static float Auto_Remove_Line;            //直线创建时，低于该长度将被自动删除
    static float Auto_Remove_Rect;            //矩形创建时，宽高低于该长度将被自动删除


    static int ToolBar_ShotArea_Gap;           //工具面板与截图区域间的间隔
    static int ToolBar_PropsBar_Gap;           //工具面本与属性面板间的间隔

    static int TextEdit_Padding_Horizontal;    //文本编辑器边框与内容间的间隔(水平方向)
    static int TextEdit_Padding_Vertical;      //文本编辑器边框与内容间的间隔(垂直顶部)
    static double TextEdit_Height_Extend;      //文本编辑器高度扩展因子

    static int ERROR_MARK_VALUE;               //mark 标注参数值错误
    static int ERROR_CLIPBOARD_VALUE;          //剪贴板参数值错误
    static int ERROR_SAVE_FORMAT;              //保存文件格式错误
    static int ERROR_SAVE_FOLDER;              //保存文件夹不存在错误

    /**
     * @brief 矩形上定位点位置枚举
     */
    enum RectAnchor
    {
        RECT_TOP_LEFT=1,
        RECT_TOP_MIDDLE=2,
        RECT_TOP_RIGHT=3,
        RECT_LEFT_MIDDLE=4,
        RECT_RIGHT_MIDDLE=5,
        RECT_BOTTOM_LEFT=6,
        RECT_BOTTOM_MIDDLE=7,
        RECT_BOTTOM_RIGHT=8
    };

    /**
     * @brief 两点间的直线距离
     * @param p1 点1
     * @param p2 点2
     * @return 距离
     */
    static float distance(QPoint p1,QPoint p2);

    /**
     * @brief 两点间的直线距离
     * @param p1 点1
     * @param p2 点2
     * @return 距离
     */
    static float distance(QPointF p1,QPointF p2);

    /**
     * @brief 点到线段的垂直距离(如果垂足不在线段上，距离为零)
     * @param p1 线段的起始点
     * @param p2 线段的结束点
     * @param p3 给定的点
     * @return 距离
     */
    static float distance(QPoint p1,QPoint p2,QPoint p3);

    /**
     * @brief 点到线段的垂直距离(如果垂足不在线段上，距离为零)
     * @param p1 线段的起始点
     * @param p2 线段的结束点
     * @param p3 给定的点
     * @return 距离
     */
    static float distance(QPointF p1,QPointF p2,QPointF p3);

    /**
     * @brief 给定的点是否在线段范围内(矩形盒子内)
     * @param p1 线段的起始点
     * @param p2 线段的结束点
     * @param p3 给定的带你
     * @return
     */
    static bool contains(QPoint p1, QPoint p2, QPoint p3);

    /*
     * 下面是下列三类定义：
     * 图形类型Key
     * 图形属性名称
     * 图形属性默认值
    */

    static QString forLineKey();
    static QString forArrowKey();
    static QString forEllipseKey();
    static QString forCurveKey();
    static QString forMosaicKey();
    static QString forRectKey();
    static QString forTextKey();

    static QString ArrowWidthName();
    static QString ArrowColorName();
    static int ArrowWidthDefault();
    static QColor ArrowColorDefault();

    static QString CurveWidthName();
    static QString CurveColorName();
    static int CurveWidthDefault();
    static QColor CurveColorDefault();

    static QString EllipseWidthName();
    static QString EllipseColorName();
    static QString EllipseStyleName();
    static int EllipseWidthDefault();
    static QColor EllipseColorDefault();
    static Qt::PenStyle EllipseStyleDefault();

    static QString LineWidthName();
    static QString LineColorName();
    static QString LineStyleName();
    static int LineWidthDefault();
    static QColor LineColorDefault();
    static Qt::PenStyle LineStyleDefault();

    static QString MosaicSizeName();
    static int MosaicSizeDefault();

    static QString RectWidthName();
    static QString RectColorName();
    static QString RectStyleName();
    static int RectWidthDefault();
    static QColor RectColorDefault();
    static Qt::PenStyle RectStyleDefault();

    static QString TextFamilyName();
    static QString TextSizeName();
    static QString TextColorName();
    static QString TextBoldName();
    static QString TextItalicName();
    static QString TextUnderlineName();
    static QString TextFamilyDefault();
    static int TextSizeDefault();
    static QColor TextColorDefault();
    static bool TextBoldDefault();
    static bool TextItalicDefault();
    static bool TextUnderlineDefault();

private:
    Utils(){};
};


#endif // SNAPCONST_H
