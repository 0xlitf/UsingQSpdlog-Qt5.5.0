QT       += core gui widgets

CONFIG += c++11

DEFINES += QT_MESSAGELOGCONTEXT

QMAKE_PROJECT_DEPTH = 0

include($$PWD/qspdlog/qspdlog.pri)

INCLUDEPATH += $$PWD/qspdlog/include
INCLUDEPATH += $$PWD/spdlog-1.2.1/include

# CONFIG(debug, debug|release) {
#     LIBS +=
# } else {
#     LIBS +=
# }

RESOURCES += \

HEADERS += \
    mainwindow.h

SOURCES += \
    main.cpp \
    mainwindow.cpp

CODECFORTR = UTF-8

msvc {
    QMAKE_CXXFLAGS += /MP
    QMAKE_CFLAGS += /MP
}

QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 5
