#-------------------------------------------------
#
# Project created by QtCreator 2017-11-02T17:20:55
#
#-------------------------------------------------

QT       += core gui printsupport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCrtAlarm
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include("wmf/wmf.pri")

INCLUDEPATH += ./database
INCLUDEPATH += ./entity
INCLUDEPATH += ./graphics
INCLUDEPATH += ./interview
INCLUDEPATH += ./widget

SOURCES += main.cpp\
        mainwindow.cpp \
    crtmaster.cpp \
    entity/crtbuilding.cpp \
    entity/crtcontroller.cpp \
    entity/crtdevice.cpp \
    entity/crtlayer.cpp \
    entity/crtloop.cpp \
    entity/crtobject.cpp \
    entity/crtproject.cpp \
    graphics/crtbackground.cpp \
    graphics/crtdeviceitem.cpp \
    graphics/crtgraphicsitem.cpp \
    graphics/crtgraphicsscene.cpp \
    graphics/crtgraphicsview.cpp \
    graphics/crttextitem.cpp \
    database/datamanager.cpp \
    database/sqliteengine.cpp \
    interview/crtcontrollerpropdelegate.cpp \
    interview/crtcontrollerpropmodel.cpp \
    interview/crtdevicepropdelegate.cpp \
    interview/crtdevicepropmodel.cpp \
    interview/crtlooppropdelegate.cpp \
    interview/crtlooppropmodel.cpp \
    interview/crtpropview.cpp \
    interview/crtsetdevicemodel.cpp \
    interview/crtsetdeviceproxymodel.cpp \
    interview/crtsetdeviceview.cpp \
    interview/crttreemodel.cpp \
    interview/crttreeview.cpp \
    widget/crtcontrollerproppanel.cpp \
    widget/crtdeviceproppanel.cpp \
    widget/crtgraphicsviewcontainer.cpp \
    widget/crtloopproppanel.cpp \
    widget/crtprojectproppanel.cpp \
    widget/crtpropertycontianer.cpp \
    widget/crtsetdevicedlg.cpp \
    widget/crttextpropdlg.cpp \
    widget/crttwowaypushbutton.cpp \
    widget/crtwelcomwidget.cpp \
    qclock.cpp \
    widget/crtstartmenu.cpp \
    crtmyiconstyle.cpp

HEADERS  += mainwindow.h \
    crtmaster.h \
    common.h \
    entity/crtbuilding.h \
    entity/crtcontroller.h \
    entity/crtdevice.h \
    entity/crtlayer.h \
    entity/crtloop.h \
    entity/crtobject.h \
    entity/crtproject.h \
    graphics/crtbackground.h \
    graphics/crtdeviceitem.h \
    graphics/crtgraphicsitem.h \
    graphics/crtgraphicsscene.h \
    graphics/crtgraphicsview.h \
    graphics/crttextitem.h \
    database/datamanager.h \
    database/sqliteengine.h \
    interview/crtcontrollerpropdelegate.h \
    interview/crtcontrollerpropmodel.h \
    interview/crtdevicepropdelegate.h \
    interview/crtdevicepropmodel.h \
    interview/crtlooppropdelegate.h \
    interview/crtlooppropmodel.h \
    interview/crtpropview.h \
    interview/crtsetdevicemodel.h \
    interview/crtsetdeviceproxymodel.h \
    interview/crtsetdeviceview.h \
    interview/crttreemodel.h \
    interview/crttreeview.h \
    widget/crtcontrollerproppanel.h \
    widget/crtdeviceproppanel.h \
    widget/crtgraphicsviewcontainer.h \
    widget/crtloopproppanel.h \
    widget/crtprojectproppanel.h \
    widget/crtpropertycontianer.h \
    widget/crtsetdevicedlg.h \
    widget/crttextpropdlg.h \
    widget/crttwowaypushbutton.h \
    widget/crtwelcomwidget.h \
    qclock.h \
    widget/crtstartmenu.h \
    crtmyiconstyle.h

RESOURCES += \
    qcrtalarm.qrc
