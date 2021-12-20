#include "localstore.h"

#include <QSettings>

LocalStore::LocalStore():Store()
{

}

void LocalStore::write(const QString &group, const QString &key, const QVariant &value)
{
    QSettings settings("./setting.ini",QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(key,value);
}

QVariant LocalStore::read(const QString &group, const QString &key, const QVariant &defaultvalue)
{
    QVariant val;
    QString keyPos=group+"/"+key;
    QSettings settings("./setting.ini",QSettings::IniFormat);
    val=settings.value(keyPos,defaultvalue);

    return val;
}
