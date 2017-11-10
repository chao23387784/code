#include "crtmyiconstyle.h"

CrtMyIconStyle::CrtMyIconStyle() :
    QCommonStyle()
{
}

int CrtMyIconStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    int n = QCommonStyle::pixelMetric(metric, option, widget);
    if(metric == QStyle::PM_SmallIconSize)
        n = 32;
    return n;
}
