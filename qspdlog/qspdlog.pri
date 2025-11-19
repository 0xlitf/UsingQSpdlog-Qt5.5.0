QT += core network
CONFIG += c++11

INCLUDEPATH += $$PWD/include/qspdlog
INCLUDEPATH += $$PWD/src

HEADERS += \
    $$PWD/include/qspdlog/optional.hpp \
    $$PWD/include/qspdlog/qabstract_spdlog_toolbar.hpp \
    $$PWD/include/qspdlog/qspdlog.hpp \
    $$PWD/include/qspdlog/string_view.hpp \
    $$PWD/include/qspdlog/qspdlog_toolbar.hpp \
    $$PWD/src/qspdlog_model.hpp \
    $$PWD/src/qspdlog_proxy_model.hpp \
    $$PWD/src/qspdlog_style_dialog.hpp \
    $$PWD/src/qt_logger_sink.hpp

RESOURCES += \
    $$PWD/src/qspdlog_resources.qrc

SOURCES += \
    $$PWD/src/qabstract_spdlog_toolbar.cpp \
    $$PWD/src/qspdlog.cpp \
    $$PWD/src/qspdlog_model.cpp \
    $$PWD/src/qspdlog_proxy_model.cpp \
    $$PWD/src/qspdlog_style_dialog.cpp \
    $$PWD/src/qspdlog_toolbar.cpp
