/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
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

