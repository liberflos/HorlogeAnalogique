#-------------------------------------------------
#
# Project created by QtCreator 2017-11-16T10:55:44
#
#-------------------------------------------------
QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Horloge_Analogique
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


SOURCES += main.cpp\
        mainwindow.cpp \
    paramheure.cpp \
    chronometre.cpp \
    minuteur.cpp \
    affichage.cpp \
    theme.cpp \
    paramreveils.cpp \
    reveilmodel.cpp \
    reveilwidget.cpp

HEADERS  += mainwindow.h \
    paramheure.h \
    chronometre.h \
    minuteur.h \
    affichage.h \
    theme.h \
    paramreveils.h \
    reveilmodel.h \
    reveilwidget.h

FORMS    += mainwindow.ui \
    paramheure.ui \
    chronometre.ui \
    minuteur.ui \
    affichage.ui \
    theme.ui \
    paramreveils.ui \
    reveilwidget.ui

DISTFILES += \
    TODO.list
