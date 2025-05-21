/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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

    void SetArgMark(const QString& m);
    void SetArgSave(const QString& s);
    void SetArgClipboard(const QString& c);
    void CleanUpArgs();
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
