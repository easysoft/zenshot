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

#include "store.h"

#include <QMetaEnum>
#include <QByteArray>

Store::Store()
{

}

void Store::writeColor(const QString &group, const QString &key, const QColor &value)
{
    QVariant tmpValue = value;
    write(group,key,tmpValue);
}

QColor Store::readColor(const QString &group, const QString &key, const QColor &defaultvalue)
{
    QVariant tmpValue = defaultvalue;
    return  read(group,key,tmpValue).value<QColor>();
}

void Store::writePenStyle(const QString &group, const QString &key, const Qt::PenStyle &value)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<Qt::PenStyle>();
    const char* strValue = metaEnum.valueToKey(value);

    QVariant varValue = strValue;
    write(group,key,varValue);
}

Qt::PenStyle Store::readPenStyle(const QString &group, const QString &key, const Qt::PenStyle &defaultvalue)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<Qt::PenStyle>();
    const char* charDefaultValue = metaEnum.valueToKey(defaultvalue);
    QString strDefaultValue(charDefaultValue);

    char* resultChar;
    QString resultStr = read(group,key,strDefaultValue).toString();
    QByteArray ba = resultStr.toLatin1();
    resultChar = ba.data();

    Qt::PenStyle result = (Qt::PenStyle)metaEnum.keysToValue(resultChar);

    return result;
}

