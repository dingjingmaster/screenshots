QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    src

SOURCES += \
    src/main.cpp \
    src/screen.cpp \
    src/screenwidget.cpp

HEADERS += \
    src/screen.h \
    src/screenwidget.h

FORMS +=

ICON = img/icon/icon.ico
