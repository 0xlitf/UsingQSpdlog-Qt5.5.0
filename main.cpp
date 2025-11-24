
#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include "spdlog/spdlog.h"
#include "mainwindow.h"
#include "logwidget.h"
// #include "fmt/ranges.h"
// #include "fmt/color.h"
// #include "fmt/compile.h"
// #include "fmt/core.h"
// #include "fmt/format.h"
// #include "fmt/format-inl.h"
// #include "fmt/locale.h"
// #include "fmt/os.h"
// #include "fmt/ostream.h"
// #include "fmt/posix.h"
// #include "fmt/printf.h"

#include "spdlog/fmt/bundled/colors.h"
#include "spdlog/fmt/bundled/core.h"
#include "spdlog/fmt/bundled/format.h"
#include "spdlog/fmt/bundled/format-inl.h"
#include "spdlog/fmt/bundled/ostream.h"
#include "spdlog/fmt/bundled/posix.h"
#include "spdlog/fmt/bundled/printf.h"
#include "spdlog/fmt/bundled/ranges.h"
#include "spdlog/fmt/bundled/time.h"

int main(int argc, char **argv) {
    Q_INIT_RESOURCE(qspdlog_resources);

    auto str = fmt::format("{}", 123);
    qDebug() << "str" << str.c_str();

    QApplication app(argc, argv);

    QFontDatabase fontDB;
    QStringList fonts = fontDB.families();
    auto fontName = QString("微软雅黑");
    if (fonts.contains(fontName)) {
        QFont font(fontName, 10);
        app.setFont(font);
    } else {
        // 回退到系统默认字体
        qDebug() << "微软雅黑字体未找到，使用系统默认字体";
    }

    // MainWindow main;
    // main.setMinimumSize(960, 720);
    // main.show();

    LogWidget main;
    main.setMinimumSize(1280, 900);
    main.show();

    int result = app.exec();
    spdlog::shutdown();

    return result;
}
