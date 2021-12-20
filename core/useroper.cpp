#include "core/useroper.h"
#include "core/utils.h"

#include <QMutex>
#include <QMutexLocker>

UserOper* UserOper::m_instance = nullptr;

UserOper* UserOper::instance()
{
    if(m_instance == nullptr)
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);

        if(m_instance == nullptr)
        {
            m_instance = new UserOper();
        }
    }

    return m_instance;
}

void UserOper::add(Command *command)
{
    UserOper::instance()->addImpl(command);
}

void UserOper::undo()
{
    UserOper::instance()->undoImpl();
}

void UserOper::redo()
{
    UserOper::instance()->redoImpl();
}

int UserOper::undoNum()
{
    return UserOper::instance()->undoNumImpl();
}

int UserOper::redoNum()
{
    return UserOper::instance()->redoNumImpl();
}

void UserOper::addImpl(Command* command)
{
    addImpl(m_undoList,command);
    emit changed();
}

void UserOper::undoImpl()
{
    if(m_undoList.count() == 0)
        return;

    Command* first = m_undoList.first();

    first->undo();
    addImpl(m_redoList,first);

    m_undoList.removeFirst();

    emit changed();
}

void UserOper::redoImpl()
{
    if(m_redoList.count() == 0)
        return;

    Command* first = m_redoList.first();

    first->redo();
    addImpl(m_undoList,first);

    m_redoList.removeFirst();

    emit changed();
}

int UserOper::undoNumImpl()
{
    return m_undoList.count();
}

int UserOper::redoNumImpl()
{
    return m_redoList.count();
}

void UserOper::addImpl(QVector<Command *> &targetList, Command *item)
{
    if(targetList.count() < Utils::Undo_Max_Count)
        targetList.prepend(item);
    else
    {
        targetList.removeLast();
        targetList.prepend(item);
    }
}
