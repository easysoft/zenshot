#ifndef APPPARAMS_H
#define APPPARAMS_H

#include<QObject>

class AppParams : public QObject
{
public:
    static AppParams* instance();

    QString mode() const;

    QString save() const;

    void init(int argc, char *argv[]);

private:
    AppParams(){};
    static AppParams* m_instance;

    QString m_mode;
    QString m_save;
};

#endif // APPPARAMS_H
