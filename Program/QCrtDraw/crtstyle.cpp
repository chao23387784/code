#include "crtstyle.h"
#include <QPainter>
#include <QStyleOption>
#include <QLinearGradient>
#include <QDebug>
#include <QFontMetrics>

CrtStyle::CrtStyle()
{

}

void CrtStyle::drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    switch(pe)
    {
//    case PE_Frame:
//    {

//    }
//        break;
    case PE_FrameTabWidget:
    {
        p->save();
        QLinearGradient lg;
        lg.setColorAt(0,QColor(96,96,96));
        lg.setColorAt(1,QColor(78,78,78));
        p->fillRect(opt->rect,lg);
        p->restore();
    }
        break;
//    case PE_PanelLineEdit:
//    {
//        p->save();
//        QLinearGradient lg;
//        lg.setColorAt(0,QColor(96,96,96));
//        lg.setColorAt(1,QColor(78,78,78));
//        p->fillRect(opt->rect,lg);
//        p->restore();
//    }
//        break;
//    case PE_IndicatorBranch:
//    {
//        p->save();
//        QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
//        lg.setColorAt(0,QColor(96,96,96));
//        lg.setColorAt(1,QColor(78,78,78));
//        p->fillRect(opt->rect,lg);
//        p->restore();
//    }
//        break;
//    case PE_PanelLineEdit:
//    {
//        p->save();
//        QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
//        lg.setColorAt(0,QColor(195,191,192));
//        lg.setColorAt(1,QColor(152,152,152));
//        p->fillRect(opt->rect,lg);
//        p->restore();
//    }
//        break;
//    case PE_IndicatorDockWidgetResizeHandle:
//    {

//    }
//        break;
//    case PE_IndicatorToolBarHandle:
//    {
//        p->save();
//        QLinearGradient lg;
//        lg.setColorAt(0,QColor(96,96,96));
//        lg.setColorAt(1,QColor(78,78,78));
//        p->fillRect(opt->rect,lg);
//        p->restore();
//    }
//        break;
//    case PE_PanelButtonCommand:
//    {
//        p->save();
//        if(opt->state & State_Raised)
//        {
//            QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
//            lg.setColorAt(0,QColor(96,96,96));
//            lg.setColorAt(1,QColor(78,78,78));
//            p->fillRect(opt->rect,lg);
//        }else if(opt->state & State_Sunken)
//        {
//            QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
//            lg.setColorAt(0,QColor(185,215,101));
//            lg.setColorAt(1,QColor(107,152,67));
//            p->fillRect(opt->rect,lg);
//        }
//        p->restore();
//    }
//        break;
    default:
        QProxyStyle::drawPrimitive(pe,opt,p,w);
    }
}

void CrtStyle::drawControl(QStyle::ControlElement element, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    switch(element)
    {
    case CE_ToolBar:
    {
        p->save();
        QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
        lg.setColorAt(0,QColor(195,191,192));
        lg.setColorAt(1,QColor(152,152,152));
        p->fillRect(opt->rect,lg);
        p->restore();
    }
        break;
//    case CE_TabBarTab:
//    {
//        const QStyleOptionTab* o = qstyleoption_cast<const QStyleOptionTab*>(opt);
//        p->save();
//        QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
//        lg.setColorAt(0,QColor(195,191,192));
//        lg.setColorAt(1,QColor(152,152,152));
//        p->fillRect(opt->rect,lg);
//        p->setPen(Qt::white);
//        p->drawText(QPoint(opt->rect.left(),opt->rect.top() + opt->rect.height()/2),o->text);
//        p->restore();
//    }
//        break;
//    case CE_TabBarTabShape:
//    {

//    }
//        break;
//    case CE_TabBarTabLabel:
//    {

//    }
//        break;
//    case CE_ToolButtonLabel:
//    {

//    }
//        break;
    case CE_DockWidgetTitle:
    {
        const QStyleOptionDockWidget* o = qstyleoption_cast<const QStyleOptionDockWidget*>(opt);
        p->save();
        p->setPen(Qt::white);
        p->drawText(QPoint(opt->rect.center().x()- opt->fontMetrics.width(o->title)/2 ,opt->rect.center().y() + 10),o->title);
        p->restore();
    }
        break;
    case CE_PushButton:
    {
        const QStyleOptionButton* o = qstyleoption_cast<const QStyleOptionButton*>(opt);
        p->save();
        if(opt->state & State_Raised)
        {
            QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
            lg.setColorAt(0,QColor(195,191,192));
            lg.setColorAt(1,QColor(152,152,152));
            p->fillRect(opt->rect,lg);
        }else if(opt->state & State_Sunken)
        {
            QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
            lg.setColorAt(0,QColor(61,203,249));
            lg.setColorAt(1,QColor(23,151,212));
            p->fillRect(opt->rect,lg);
        }
        p->setPen(Qt::white);
        p->drawText(QPoint(opt->rect.center().x()- opt->fontMetrics.width(o->text)/2 ,opt->rect.center().y() + 5),o->text);
        p->restore();
    }
        break;
//    case CE_ItemViewItem:
//    {
//        const QStyleOptionViewItem* o = qstyleoption_cast<const QStyleOptionViewItem*>(opt);
//        p->save();
//        if(!(opt->state & State_Selected))
//        {
//            QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
//            lg.setColorAt(0,QColor(96,96,96));
//            lg.setColorAt(1,QColor(78,78,78));
//            p->fillRect(opt->rect,lg);
//        }else if(opt->state & State_Selected)
//        {
//            QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
//            lg.setColorAt(0,QColor(61,203,249));
//            lg.setColorAt(1,QColor(23,151,212));
//            p->fillRect(opt->rect,lg);
//        }
//        p->setPen(Qt::white);
//        p->drawText(QPoint(opt->rect.left()+5,opt->rect.top() + opt->rect.height()/2 + 5),o->text);
//        p->restore();
//    }
//        break;
    case CE_HeaderEmptyArea:
    {
        p->save();
        QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
        lg.setColorAt(0,QColor(220,220,220));
        lg.setColorAt(1,QColor(148,148,148));
        p->fillRect(opt->rect,lg);
        p->restore();
    }
        break;
    case CE_Header:
    {
        const QStyleOptionHeader* o = qstyleoption_cast<const QStyleOptionHeader*>(opt);
        p->save();
        QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
        lg.setColorAt(0,QColor(220,220,220));
        lg.setColorAt(1,QColor(148,148,148));
        p->fillRect(opt->rect,lg);
        p->setPen(Qt::black);
        p->drawText(QPoint(opt->rect.center().x()- opt->fontMetrics.width(o->text)/2,opt->rect.center().y() + 5),o->text);
        p->restore();
    }
        break;
//    case CE_ComboBoxLabel:
//    {
//        const QStyleOptionComboBox* o = qstyleoption_cast<const QStyleOptionComboBox*>(opt);
//        p->save();
//        p->setPen(Qt::white);
//        p->drawText(QPoint(opt->rect.left()+5,opt->rect.top() + opt->rect.height()/2 + 5),o->currentText);
//        p->restore();
//    }
//        break;
//    case CE_ShapedFrame:
//    {

//    }
//        break;
    default:
        QProxyStyle::drawControl(element,opt,p,w);
    }
}

QRect CrtStyle::subElementRect(QStyle::SubElement r, const QStyleOption *opt, const QWidget *widget) const
{
    return QProxyStyle::subElementRect(r,opt,widget);
}

void CrtStyle::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *w) const
{
    switch(cc)
    {
//    case CC_ComboBox:
//    {
//        //const QStyleOptionHeader* o = qstyleoption_cast<const QStyleOptionHeader*>(opt);
//        p->save();
//        QLinearGradient lg(opt->rect.topLeft(),opt->rect.bottomLeft());
//        lg.setColorAt(0,QColor(220,220,220));
//        lg.setColorAt(1,QColor(148,148,148));
//        p->fillRect(opt->rect,lg);
//        //p->setPen(Qt::black);
//        //p->drawText(QPoint(opt->rect.center().x()- opt->fontMetrics.width(o->text)/2,opt->rect.center().y() + 5),o->text);
//        p->restore();
//    }
//        break;
    default:
        QProxyStyle::drawComplexControl(cc,opt,p,w);
    }
}

QStyle::SubControl CrtStyle::hitTestComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, const QPoint &pt, const QWidget *w) const
{
    return QProxyStyle::hitTestComplexControl(cc,opt,pt,w);
}

QRect CrtStyle::subControlRect(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QStyle::SubControl sc, const QWidget *w) const
{
    return QProxyStyle::subControlRect(cc,opt,sc,w);
}

QSize CrtStyle::sizeFromContents(QStyle::ContentsType ct, const QStyleOption *opt, const QSize &contentsSize, const QWidget *widget) const
{
    return QProxyStyle::sizeFromContents(ct,opt,contentsSize,widget);
}

int CrtStyle::pixelMetric(QStyle::PixelMetric m, const QStyleOption *opt, const QWidget *widget) const
{
    return QProxyStyle::pixelMetric(m,opt,widget);
}

int CrtStyle::styleHint(QStyle::StyleHint sh, const QStyleOption *opt, const QWidget *w, QStyleHintReturn *shret) const
{
    return QProxyStyle::styleHint(sh,opt,w,shret);
}

QIcon CrtStyle::standardIcon(QStyle::StandardPixmap standardIcon, const QStyleOption *opt, const QWidget *widget) const
{
    return QProxyStyle::standardIcon(standardIcon,opt,widget);
}

QPixmap CrtStyle::standardPixmap(QStyle::StandardPixmap sp, const QStyleOption *opt, const QWidget *widget) const
{
    return QProxyStyle::standardPixmap(sp,opt,widget);
}

QPixmap CrtStyle::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *opt) const
{
    return QProxyStyle::generatedIconPixmap(iconMode,pixmap,opt);
}

int CrtStyle::layoutSpacing(QSizePolicy::ControlType control1, QSizePolicy::ControlType control2, Qt::Orientation orientation, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::layoutSpacing(control1,control2,orientation,option,widget);
}

void CrtStyle::polish(QPalette &palette)
{
    QLinearGradient lg;
    lg.setColorAt(0,QColor(96,96,96));
    lg.setColorAt(1,QColor(78,78,78));
    QColor bronze(207,155,95);
    QColor veryLightBlue(239,239,247);
    QColor lightBlue(223,223,239);
    QColor darkBlue(74,144,217);

    palette=QPalette(bronze);
    palette.setBrush(QPalette::Window,lg);
    palette.setBrush(QPalette::BrightText, Qt::white);
    palette.setBrush(QPalette::Base, veryLightBlue);
    palette.setBrush(QPalette::AlternateBase, lightBlue);
    palette.setBrush(QPalette::Highlight, darkBlue);
    palette.setBrush(QPalette::Disabled, QPalette::Highlight,Qt::darkGray);
}

void CrtStyle::polish(QApplication *app)
{
    QProxyStyle::polish(app);
}

void CrtStyle::polish(QWidget *widget)
{
    QProxyStyle::polish(widget);
}

void CrtStyle::unpolish(QWidget *widget)
{
    QProxyStyle::unpolish(widget);
}

void CrtStyle::unpolish(QApplication *application)
{
    QProxyStyle::unpolish(application);
}

