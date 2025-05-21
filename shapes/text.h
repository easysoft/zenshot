/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#ifndef TEXT_H
#define TEXT_H

#include "core/shape.h"

class Text : public Shape
{
public:
    explicit Text(Workspace *m_workspace);

public:
    QString type();
    void move(QPoint offsetPoint);
    QVector<Handle *> handles();
    QRect boundary();
    void draw(QPainter &painter);
    bool contain(QPoint point);

    QFont font();

    QString content() const;
    void setContent(const QString &value);

    QColor color() const;
    void setColor(const QColor &color);

    QPoint location() const;
    void setLocation(const QPoint &value);

protected:
    void loadPropsImpl(Store *store);
    void savePropsImpl(Store *store);

private:
    int m_size;
    bool m_italic;
    bool m_underline;
    int m_weight;
    QString m_family;
    QColor m_color;

    QPoint m_location;
    QString m_content;

};

#endif // TEXT_H
