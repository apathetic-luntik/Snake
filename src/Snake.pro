#-------------------------------------------------
#
# Project created by QtCreator 2025-02-20T09:56:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    levels.cpp \
    scores.cpp \
    gamescreen.cpp \
    record.cpp \
    snake_model.cpp \
    table_model.cpp \
    log.cpp \
    log.cpp \
    create_level.cpp

HEADERS += \
        mainwindow.h \
    levels.h \
    scores.h \
    gamescreen.h \
    record.h \
    snake_model.h \
    table_model.h \
    type_direction.h \
    log.h \
    log.h \
    create_level.h

FORMS += \
        mainwindow.ui \
    levels.ui \
    scores.ui \
    gamescreen.ui \
    record.ui \
    create_level.ui

DISTFILES += \
    scores_level2 \
    bin/levels \
    bin/scores_level1
