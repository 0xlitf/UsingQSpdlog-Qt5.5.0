
#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include "spdlog/spdlog.h"
#include "mainwindow.h"
#include "logwidget.h"

int main(int argc, char **argv) {
    Q_INIT_RESOURCE(qspdlog_resources);


    QApplication app(argc, argv);

    QFontDatabase fontDB;
    QStringList fonts = fontDB.families();
    auto fontName = QString("微软雅黑");
    if (fonts.contains(fontName)) {
        QFont font(fontName, 10);
        qApp->setFont(font);
    } else {
        // 回退到系统默认字体
        qDebug() << "微软雅黑字体未找到，使用系统默认字体";
    }

    // MainWindow main;
    // main.setMinimumSize(960, 720);
    // main.show();

    LogWidget main;
    main.setMinimumSize(960, 720);
    main.show();

    int result = app.exec();
    spdlog::shutdown();

    return result;
}
