#-------------------------------------------------
#
# Project created by QtCreator 2019-11-05T15:59:15
#
#-------------------------------------------------

QT       += core gui network widgets webkit


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

   contains(QT_VERSION, ^5.*) {
       QT += webkitwidgets
   }

RCC_DIR = tmp/RCC
MOC_DIR = tmp/MOC
OBJECTS_DIR = tmp/OBJ
UI_DIR = tmp/UIC

TARGET = InsagramMetric
TEMPLATE = app


SOURCES += main.cpp\
        instmetric.cpp \
    basicmetric.cpp \
    httpwindow.cpp \
    webjs/base/d3viewer.cpp \
    webjs/base/d3webpage.cpp \
    webjs/charts/pie/dependencywheelwidget.cpp

HEADERS  += instmetric.h \
    basicmetric.h \
    editFileHTML.h \
    FileHTMLPublic/httpwindow.h \
    httpwindow.h \
    webjs/base/d3viewer.h \
    webjs/base/d3webpage.h \
    webjs/charts/pie/dependencywheelwidget.h

FORMS +=

OTHER_FILES +=

RESOURCES +=


