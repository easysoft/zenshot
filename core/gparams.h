#ifndef APPPARAMS_H
#define APPPARAMS_H

#include<QObject>

class GParams : public QObject
{
public:
    static GParams* instance();

    QString mark() const;

    QString save() const;

    float scale() const;
    void setScale(float scale);

    QString clipboard() const;
    void setClipboard(const QString &clipboard);

    int fromArgs(int argc, char *argv[]);

private:
    GParams(){};
    static GParams* m_instance;

    QString m_mark;
    QString m_save;
    QString m_clipboard;

    float m_scale;
};

#endif // APPPARAMS_H
