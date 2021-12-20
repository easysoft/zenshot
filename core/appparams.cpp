#include "appparams.h"
#include <QMutex>
#include <QMutexLocker>

AppParams* AppParams::m_instance = nullptr;

AppParams* AppParams::instance()
{
    if(m_instance == nullptr)
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);

        if(m_instance == nullptr)
        {
            m_instance = new AppParams();
        }
    }

    return m_instance;
}

QString AppParams::mode() const
{
    return m_mode;
}

QString AppParams::save() const
{
    return m_save;
}

void AppParams::init(int argc, char *argv[])
{
    m_mode = "edit";
    m_save = "clipboard";

    for(int i=0;i<argc;i++)
    {
        char *c = argv[i];
        QString str(c);

        if(str.startsWith("mode="))
            m_mode = str.mid(5);
        else if(str.startsWith("save="))
            m_save = str.mid(5);
    }
}
