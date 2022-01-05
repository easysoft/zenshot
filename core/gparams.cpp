#include "gparams.h"
#include "core/utils.h"

#include <QMutex>
#include <QMutexLocker>

GParams* GParams::m_instance = nullptr;

GParams* GParams::instance()
{
    if(m_instance == nullptr)
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);

        if(m_instance == nullptr)
        {
            m_instance = new GParams();
            m_instance->setScale(1.0);
        }
    }

    return m_instance;
}

QString GParams::mark() const
{
    return m_mark;
}

QString GParams::save() const
{
    return m_save;
}

int GParams::fromArgs(int argc, char *argv[])
{
    m_mark = "yes";
    m_clipboard = "auto";
    m_save = nullptr;

    for(int i=0;i<argc;i++)
    {
        char *c = argv[i];
        QString str(c);

        if(str.startsWith("--mark="))
            m_mark = str.mid(7);
        else if(str.startsWith("-m="))
            m_mark = str.mid(3);
        else if(str.startsWith("--save="))
            m_save = str.mid(7);
        else if(str.startsWith("-s="))
            m_save = str.mid(3);
        else if(str.startsWith("--clipboard="))
            m_clipboard = str.mid(12);
        else if(str.startsWith("-c="))
            m_clipboard = str.mid(3);
    }

    if(m_mark != "yes" && m_mark != "no")
        return Utils::ERROR_MARK_VALUE;

    if(m_clipboard != "auto" && m_clipboard != "yes" && m_clipboard != "no")
        return Utils::ERROR_CLIPBOARD_VALUE;

    return 0;
}

QString GParams::clipboard() const
{
    return m_clipboard;
}

void GParams::setClipboard(const QString &clipboard)
{
    m_clipboard = clipboard;
}

float GParams::scale() const
{
    return m_scale;
}

void GParams::setScale(float scale)
{
    m_scale = scale;
}
