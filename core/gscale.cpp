#include "gscale.h"
#include "core/gparams.h"

#include <QtMath>

GScale::GScale()
{

}

float GScale::ts(float pxValue)
{
    float s = GParams::instance()->scale();

    float v = pxValue * s;

    float minV = 1.0;

    if(v == 0.0) return 0;

    return qRound(qMax(minV,v));
}
