#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T08:31:50
#
#-------------------------------------------------

QT       += core gui printsupport sql
RC_ICONS += ./img/draw.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCrtDraw
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
    database/datamanager.cpp \
    database/sqliteengine.cpp \
    entity/crtbuilding.cpp \
    entity/crtcontroller.cpp \
    entity/crtdevice.cpp \
    entity/crtlayer.cpp \
    entity/crtloop.cpp \
    entity/crtobject.cpp \
    entity/crtproject.cpp \
    graphics/crtbackground.cpp \
    graphics/crtdeviceitem.cpp \
    interview/crttreemodel.cpp \
    interview/crttreeview.cpp \
    widget/crtloopproppanel.cpp \
    widget/crtprojectproppanel.cpp \
    widget/crtpropertycontianer.cpp \
    widget/crttwowaypushbutton.cpp \
    widget/crtwelcomwidget.cpp \
    widget/crtcontrollerproppanel.cpp \
    widget/crtdeviceproppanel.cpp \
    interview/crtcontrollerpropmodel.cpp \
    interview/crtlooppropmodel.cpp \
    interview/crtdevicepropmodel.cpp \
    interview/crtcontrollerpropdelegate.cpp \
    interview/crtlooppropdelegate.cpp \
    interview/crtdevicepropdelegate.cpp \
    interview/crtpropview.cpp \
    graphics/crtgraphicsview.cpp \
    graphics/crtgraphicsscene.cpp \
    widget/crtgraphicsviewcontainer.cpp \
    widget/crtsetdevicedlg.cpp \
    interview/crtsetdevicemodel.cpp \
    interview/crtsetdeviceproxymodel.cpp

HEADERS  += mainwindow.h \
    crtmaster.h \
    common.h \
    database/datamanager.h \
    database/sqliteengine.h \
    entity/crtbuilding.h \
    entity/crtcontroller.h \
    entity/crtdevice.h \
    entity/crtlayer.h \
    entity/crtloop.h \
    entity/crtobject.h \
    entity/crtproject.h \
    graphics/crtbackground.h \
    graphics/crtdeviceitem.h \
    interview/crttreemodel.h \
    interview/crttreeview.h \
    widget/crtloopproppanel.h \
    widget/crtprojectproppanel.h \
    widget/crtpropertycontianer.h \
    widget/crttwowaypushbutton.h \
    widget/crtwelcomwidget.h \
    widget/crtcontrollerproppanel.h \
    widget/crtdeviceproppanel.h \
    interview/crtcontrollerpropmodel.h \
    interview/crtlooppropmodel.h \
    interview/crtdevicepropmodel.h \
    interview/crtcontrollerpropdelegate.h \
    interview/crtlooppropdelegate.h \
    interview/crtdevicepropdelegate.h \
    interview/crtpropview.h \
    graphics/crtgraphicsview.h \
    graphics/crtgraphicsscene.h \
    widget/crtgraphicsviewcontainer.h \
    widget/crtsetdevicedlg.h \
    interview/crtsetdevicemodel.h \
    interview/crtsetdeviceproxymodel.h

DISTFILES +=

RESOURCES += \
    qcrtdraw.qrc
