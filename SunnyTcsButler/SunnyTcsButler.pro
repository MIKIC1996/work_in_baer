#-------------------------------------------------
#
# Project created by QtCreator 2021-01-25T10:29:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SunnyTcsButler
TEMPLATE = app


SOURCES += \
    configsetdig.cpp \
    main.cpp \
    mainwindow.cpp \
    sunnytcsconfig.cpp \
    sunnytcsconfigcenter.cpp \
    sunnytcsconfigitem.cpp \
    sunnytcsfilesetdig.cpp \
    sunnytcsservice.cpp \
    sunytcstreeitem.cpp \
    sunnytcsprocedureconfigdig.cpp \
    sunnytcsprocedureexedig.cpp \
    sunnytcsprocedureaction.cpp \
    sunnytcsprocedurechilddig.cpp

HEADERS  += \
    configsetdig.h \
    mainwindow.h \
    sunnytcsconfig.h \
    sunnytcsconfigcenter.h \
    sunnytcsconfigitem.h \
    sunnytcsfilesetdig.h \
    sunnytcsservice.h \
    sunytcstreeitem.h \
    sunnytcsprocedureconfigdig.h \
    sunnytcsprocedureexedig.h \
    sunnytcsprocedureaction.h \
    sunnytcsprocedurechilddig.h

FORMS    += \
    configsetdig.ui \
    mainwindow.ui \
    sunnytcsfilesetdig.ui \
    sunnytcsprocedureconfigdig.ui \
    sunnytcsprocedureexedig.ui \
    sunnytcsprocedurechilddig.ui

RESOURCES += \
    res.qrc

DISTFILES +=
