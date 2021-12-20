#include "arrow.h"
#include <QtMath>

Arrow::Arrow(Workspace *workspace):PointsShape(workspace)
{
    loadProps();
}

QString Arrow::type()
{
    return  Utils::forArrowKey();
}

QPainterPath Arrow::getPath()
{
    QPainterPath path;

    //初始化等边三角箭头的边长
    double side = m_lineWidth * 2;

    QPoint start = pointAt(0);
    QPoint end = pointAt(1);

    //调整实际绘制采用的边长(箭头的大小跟随线段的长度逐渐变大，线段长度达到参考长度时箭头达到设置的大小并且之后不再变大)
    double  referLength = side * 2;
    double lineLength = Utils::distance(start,end);

    double realSide = (m_lineWidth/ referLength)*lineLength;

    if(realSide > side)
    {
        realSide = side;
    }

    //计算箭头(等边三角形)的高
    double height = realSide * qSin(60.0/180.0*M_PI);

    //计算直线(start,end组成的直线)与坐标轴的夹角
    double qatan2 = qAtan2(end.y()-start.y(),end.x()-start.x());
    double angle = qatan2*180/M_PI;

    //计算箭头底边与直线交点的坐标
    double cx = start.x() + (lineLength-height)*qCos(angle/180.0*M_PI);
    double cy = start.y() + (lineLength-height)*qSin(angle/180.0*M_PI);

    //计算箭头底边向箭头顶端偏移一地距离后与直线交点的坐标
    double ocx = start.x() + (lineLength-height*0.7)*qCos(angle/180.0*M_PI);
    double ocy = start.y() + (lineLength-height*0.7)*qSin(angle/180.0*M_PI);

    //下面构造箭头的路径点

    //起始点
    path.moveTo(start);

    //上方的第一个点(非尖点)
    double upAngle = angle - 90;

    double upX1 = ocx + realSide*0.4/2*qCos(upAngle/180.0*M_PI);
    double upY1 = ocy + realSide*0.4/2*qSin(upAngle/180.0*M_PI);

    path.lineTo(upX1,upY1);

    //上方的第二个点(尖点)
    double upX2 = cx + realSide/2*qCos(upAngle/180.0*M_PI);
    double upY2 = cy + realSide/2*qSin(upAngle/180.0*M_PI);

    path.lineTo(upX2,upY2);

    //结束点
    path.lineTo(end);

    //下方的第二个点(尖点)
    double downAngle = angle + 90;

    double downX2 = cx + realSide/2*qCos(downAngle/180.0*M_PI);
    double downY2 = cy + realSide/2*qSin(downAngle/180.0*M_PI);

    path.lineTo(downX2,downY2);

    //下方的第一个点(非尖点)
    double downX1 = ocx + realSide*0.4/2*qCos(downAngle/180.0*M_PI);
    double downY1 = ocy + realSide*0.4/2*qSin(downAngle/180.0*M_PI);

    path.lineTo(downX1,downY1);

    //闭合路径
    path.lineTo(start);

    return path;
}

bool Arrow::contain(QPoint point)
{
    QPainterPath path = getPath();
    return path.contains(point);
}

void Arrow::draw(QPainter &painter)
{
    painter.save();

    QPen pen;
    pen.setColor(m_lineColor);

    QBrush brush;
    brush.setColor(m_lineColor);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);

    QPainterPath path = getPath();
    //painter.drawPath(path);
    painter.fillPath(path,brush);

    painter.restore();
}

void Arrow::loadPropsImpl(Store *store)
{
    m_lineWidth = store->read(Utils::forArrowKey(),Utils::ArrowWidthName(),Utils::ArrowWidthDefault()).toInt();
    m_lineColor = store->readColor(Utils::forArrowKey(),Utils::ArrowColorName(),Utils::ArrowColorDefault());
}

void Arrow::savePropsImpl(Store *store)
{
    store->write(Utils::forArrowKey(),Utils::ArrowWidthName(),m_lineWidth);
    store->writeColor(Utils::forArrowKey(),Utils::ArrowColorName(),m_lineColor);
}



