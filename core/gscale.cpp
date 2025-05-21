/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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
