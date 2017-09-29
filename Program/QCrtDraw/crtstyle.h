#ifndef CRTSTYLE_H
#define CRTSTYLE_H
#include <QProxyStyle>

class CrtStyle : public QProxyStyle
{
public:
    CrtStyle();
    void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
                       const QWidget *w = 0) const;
    void drawControl(ControlElement element, const QStyleOption *opt, QPainter *p,
                     const QWidget *w = 0) const;
    QRect subElementRect(SubElement r, const QStyleOption *opt, const QWidget *widget = 0) const;
    void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p,
                            const QWidget *w = 0) const;
    SubControl hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex *opt,
                                     const QPoint &pt, const QWidget *w = 0) const;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc,
                         const QWidget *w = 0) const;
    QSize sizeFromContents(ContentsType ct, const QStyleOption *opt,
                           const QSize &contentsSize, const QWidget *widget = 0) const;

    int pixelMetric(PixelMetric m, const QStyleOption *opt = 0, const QWidget *widget = 0) const;

    int styleHint(StyleHint sh, const QStyleOption *opt = 0, const QWidget *w = 0,
                  QStyleHintReturn *shret = 0) const;

    QIcon standardIcon(StandardPixmap standardIcon, const QStyleOption *opt = 0,
                       const QWidget *widget = 0) const;
    QPixmap standardPixmap(StandardPixmap sp, const QStyleOption *opt = 0,
                           const QWidget *widget = 0) const;

    QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap,
                                const QStyleOption *opt) const;
    int layoutSpacing(QSizePolicy::ControlType control1, QSizePolicy::ControlType control2,
                      Qt::Orientation orientation, const QStyleOption *option = 0,
                      const QWidget *widget = 0) const;

    void polish(QPalette &palette);
    void polish(QApplication *app);
    void polish(QWidget *widget);
    void unpolish(QWidget *widget);
    void unpolish(QApplication *application);
};

#endif // CRTSTYLE_H
