QT       += core gui widgets

CONFIG += c++11

DEFINES += QT_MESSAGELOGCONTEXT

QMAKE_PROJECT_DEPTH = 0

include($$PWD/qspdlog/qspdlog.pri)
include($$PWD/compile.pri)

INCLUDEPATH += $$PWD/qspdlog/include
INCLUDEPATH += $$PWD/spdlog-1.2.1/include
INCLUDEPATH += C:/GitHub/fmt-5.0.0/include

# CONFIG(debug, debug|release) {
#     LIBS +=
# } else {
#     LIBS +=
# }

RESOURCES += \

HEADERS += \
    controls/checkbox.h \
    controls/controls.h \
    controls/layoutbuilder.h \
    controls/lineedit.h \
    controls/memorymonitorwidget.h \
    controls/normalbutton.h \
    controls/pagetabbutton.h \
    controls/smartaspectratiolabel.h \
    controls/widgetbase.h \
    logger.h \
    logwidget.h \
    mainwindow.h

SOURCES += \
    controls/checkbox.cpp \
    controls/layoutbuilder.cpp \
    controls/lineedit.cpp \
    controls/memorymonitorwidget.cpp \
    controls/normalbutton.cpp \
    controls/pagetabbutton.cpp \
    controls/smartaspectratiolabel.cpp \
    controls/widgetbase.cpp \
    logger.cpp \
    logwidget.cpp \
    main.cpp \
    mainwindow.cpp

CODECFORTR = UTF-8

msvc {
    QMAKE_CXXFLAGS += /MP
    QMAKE_CFLAGS += /MP
}

QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 5
