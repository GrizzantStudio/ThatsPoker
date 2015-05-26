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
    handbrowser.cpp \
    flopboardbrowser.cpp \
    computehandprobastep1.cpp \
    handcategorizerstrategy.cpp \
    computeflophandprobastrategy.cpp \
    handcategory.cpp \
    combinaisontype.cpp \
    combinaison.cpp \
    computeflopturnriverhandprobastrategy.cpp \
    flopturnriverboardbrowser.cpp

HEADERS  += mainwindow.h \
    types.h \
    cardmapper.h \
    maths.h \
    processor.h \
    cardsetbrowser.h \
    handbrowser.h \
    cardsetbrowserstrategy.h \
    flopboardbrowser.h \
    displaycardsetsstrategy.h \
    computehandprobastep1.h \
    handcategorizerstrategy.h \
    computeflophandprobastrategy.h \
    handcategory.h \
    evaluator.h \
    combinaisontype.h \
    combinaison.h \
    computeflopturnriverhandprobastrategy.h \
    flopturnriverboardbrowser.h

FORMS    += mainwindow.ui

INCLUDEPATH += .
