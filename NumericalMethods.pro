#-------------------------------------------------
#
# Project created by QtCreator 2017-11-15T10:25:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NumericalMethods
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


SOURCES += \
        main.cpp \
        numethods.cpp \
    punto.cpp \
    newson.cpp \
    gausss.cpp \
    gausei.cpp \
    ilagrange.cpp \
    reglin.cpp \
    regmul.cpp \
    difnum.cpp \
    integnum.cpp \
    meuler.cpp \
    runtta.cpp

HEADERS += \
        numethods.h \
    punto.h \
    newson.h \
    gausss.h \
    gausei.h \
    ilagrange.h \
    reglin.h \
    regmul.h \
    difnum.h \
    integnum.h \
    meuler.h \
    runtta.h

FORMS += \
        numethods.ui \
    punto.ui \
    newson.ui \
    gausss.ui \
    gausei.ui \
    ilagrange.ui \
    reglin.ui \
    regmul.ui \
    difnum.ui \
    integnum.ui \
    meuler.ui \
    runtta.ui

RESOURCES += \
    imagenes.qrc
