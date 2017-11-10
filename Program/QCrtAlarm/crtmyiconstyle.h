#ifndef CMYICONSTYLE_H
#define CMYICONSTYLE_H

#include <QCommonStyle>

class CrtMyIconStyle : public QCommonStyle
{
    Q_OBJECT
public:
    CrtMyIconStyle();
    int pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const;
};

#endif // CMYICONSTYLE_H
