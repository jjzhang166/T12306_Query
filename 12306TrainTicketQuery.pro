#-------------------------------------------------
#
# Project created by QtCreator 2015-05-21T15:03:47
#
#-------------------------------------------------

QT       += core    gui    network webkit   webkitwidgets widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 12306TrainTicketQuery
TEMPLATE = app


SOURCES += main.cpp\
        T12306.cpp \
    StringListModel.cpp

HEADERS  += T12306.h \
    StringListModel.h

FORMS    += T12306.ui
