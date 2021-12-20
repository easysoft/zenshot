#ifndef AREALOCATOR_H
#define AREALOCATOR_H

#include "core/locator.h"
#include "core/utils.h"

class ShotArea;

class AreaLocator : public Locator
{
public:
    AreaLocator(ShotArea* shape,Utils::RectAnchor anchor);

    Utils::RectAnchor anchor() const;
    void setAnchor(const Utils::RectAnchor &anchor);

    QPoint location();
    void setLocation(QPoint point);

private:
    Utils::RectAnchor m_anchor;
    ShotArea* m_shotArea;
};

#endif // AREALOCATOR_H
