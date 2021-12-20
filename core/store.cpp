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

