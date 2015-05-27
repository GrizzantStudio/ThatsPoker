#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T20:07:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ThatsPoker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cardmapper.cpp \
    maths.cpp \
    processor.cpp \
    handcategorizerstrategy.cpp \
    handcategory.cpp \
    combinaisontype.cpp \
    combinaison.cpp

HEADERS  += mainwindow.h \
    types.h \
    cardmapper.h \
    maths.h \
    processor.h \
    cardsetbrowser.h \
    cardsetbrowserstrategy.h \
    displaycardsetsstrategy.h \
    handcategorizerstrategy.h \
    handcategory.h \
    evaluator.h \
    combinaisontype.h \
    combinaison.h \
    evaluatecardsetwithhandstrategy.h

FORMS    += mainwindow.ui

INCLUDEPATH += .
