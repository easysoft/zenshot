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

#include "utils.h"
#include "QtMath"
#include <QFont>
#include <QPoint>

int Utils::Handle_Area_Size = 9;
int Utils::Handle_Area_Border_Thickness = 1;
QColor Utils::Handle_Area_Border_Color = QColor(128,128,128);
QColor Utils::Handle_Area_Fill_Color = QColor(255,255,255);

int Utils::Handle_Shape_Size = 9;
int Utils::Handle_Shape_Border_Thickness = 1;
QColor Utils::Handle_Shape_Border_Color = QColor(128,128,128);
QColor Utils::Handle_Shape_Fill_Color = QColor(255,255,255);

QColor Utils::Handle_AntLine_Color = QColor(128,128,128);
QColor Utils::Handle_AntLine_SubColor = QColor(255,255,255);
int Utils::Handle_AntLine_Thicknes = 1;

int Utils::Undo_Max_Count = 100;

int Utils::Hit_Snap = 3;

float Utils::Auto_Remove_Line = 2.0;
float Utils::Auto_Remove_Rect = 2.0;

int Utils::ToolBar_ShotArea_Gap = 8; //12
int Utils::ToolBar_PropsBar_Gap = 5;  //8

int Utils::TextEdit_Padding_Horizontal = 5;//5
int Utils::TextEdit_Padding_Vertical = 8;  //8
double Utils::TextEdit_Height_Extend = 0.5; //0.5

int Utils::ERROR_MARK_VALUE = 2;
int Utils::ERROR_CLIPBOARD_VALUE = 3;
int Utils::ERROR_SAVE_FORMAT = 4;
int Utils::ERROR_SAVE_FOLDER = 5;


float Utils::distance(QPoint p1, QPoint p2)
{
    QPointF tp1 = QPointF(p1);
    QPointF tp2 = QPointF(p2);

    return distance(tp1,tp2);
}

float Utils::distance(QPointF p1, QPointF p2)
{
    float dx = p1.x() - p2.x();
    float dy = p1.y() - p2.y();

    return qSqrt(dx*dx + dy*dy);
}

float Utils::distance(QPoint p1, QPoint p2, QPoint p3)
{
    QPointF tp1 = QPointF(p1);
    QPointF tp2 = QPointF(p2);
    QPointF tp3 = QPointF(p3);

    return distance(tp1,tp2,tp3);
}

float Utils::distance(QPointF p1, QPointF p2,QPointF p)
{
    float reVal = 0;
    float retData = false;

    float x1 = p1.x();
    float y1 = p1.y();

    float x2 = p2.x();
    float y2 = p2.y();

    float x = p.x();
    float y = p.y();

    float cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
    if (cross <= 0)
    {
        reVal = (float)qSqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
        retData = true;
    }

    float d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    if (cross >= d2)
    {
        reVal = (float)qSqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        retData = true;
    }

    if (!retData)
    {
         float r = cross / d2;
         float px = x1 + (x2 - x1) * r;
         float py = y1 + (y2 - y1) * r;

         reVal = (float)qSqrt((x - px) * (x - px) + (py - y) * (py - y));
    }

    return reVal;
}

bool Utils::contains(QPoint p1, QPoint p2, QPoint p3)
{
    float x1 = qMin(p1.x(),p2.x());
    float x2 = qMax(p1.x(),p2.x());

    float y1 = qMin(p1.y(),p2.y());
    float y2 = qMax(p1.y(),p2.y());

    if(p3.x() < x1 || p3.x() > x2 || p3.y() < y1 || p3.y() > y2)
    {
        return false;
    }

    return true;
}

QString Utils::forLineKey()
{
    return  "line";
}

QString Utils::forArrowKey()
{
    return  "arrow";
}

QString Utils::forEllipseKey()
{
    return  "ellipse";
}

QString Utils::forCurveKey()
{
    return  "curve";
}

QString Utils::forMosaicKey()
{
    return  "mosaic";
}

QString Utils::forRectKey()
{
    return  "rectanlge";
}

QString Utils::forTextKey()
{
    return  "text";
}

QString Utils::ArrowWidthName()
{
    return "width";
}

QString Utils::ArrowColorName()
{
    return "color";
}

int Utils::ArrowWidthDefault()
{
    return 12;
}

QColor Utils::ArrowColorDefault()
{
    return QColor(242,69,61);
}

QString Utils::CurveWidthName()
{
    return "line_width";
}

QString Utils::CurveColorName()
{
    return "line_color";
}

int Utils::CurveWidthDefault()
{
    return 2;
}

QColor Utils::CurveColorDefault()
{
    return QColor(242,69,61);
}

QString Utils::EllipseWidthName()
{
    return "line_width";
}

QString Utils::EllipseColorName()
{
    return "line_color";
}

QString Utils::EllipseStyleName()
{
    return "line_style";
}

int Utils::EllipseWidthDefault()
{
    return 2;
}

QColor Utils::EllipseColorDefault()
{
    return QColor(242,69,61);
}

Qt::PenStyle Utils::EllipseStyleDefault()
{
    return Qt::SolidLine;
}


QString Utils::LineWidthName()
{
    return "line_width";
}

QString Utils::LineColorName()
{
    return "line_color";
}

QString Utils::LineStyleName()
{
    return "line_style";
}

int Utils::LineWidthDefault()
{
    return 2;
}

QColor Utils::LineColorDefault()
{
    return QColor(242,69,61);
}

Qt::PenStyle Utils::LineStyleDefault()
{
    return Qt::SolidLine;
}

QString Utils::MosaicSizeName()
{
    return "size";
}

int Utils::MosaicSizeDefault()
{
    return 8;
}

QString Utils::RectWidthName()
{
    return "line_width";
}

QString Utils::RectColorName()
{
    return "line_color";
}

QString Utils::RectStyleName()
{
    return "line_style";
}

int Utils::RectWidthDefault()
{
    return 2;
}

QColor Utils::RectColorDefault()
{
    return QColor(242,69,61);
}

Qt::PenStyle Utils::RectStyleDefault()
{
    return Qt::SolidLine;
}

QString Utils::TextFamilyName()
{
    return "font_family";
}

QString Utils::TextSizeName()
{
    return "font_size";
}

QString Utils::TextColorName()
{
    return "font_color";
}

QString Utils::TextBoldName()
{
    return "bold";
}

QString Utils::TextItalicName()
{
    return "italic";
}

QString Utils::TextUnderlineName()
{
    return "underline";
}

QString Utils::TextFamilyDefault()
{
    QFont font;
    return font.family();
}

int Utils::TextSizeDefault()
{
    return 24;
}

QColor Utils::TextColorDefault()
{
    return QColor(242,69,61);
}

bool Utils::TextBoldDefault()
{
    return false;
}

bool Utils::TextItalicDefault()
{
    return false;
}

bool Utils::TextUnderlineDefault()
{
    return false;
}


