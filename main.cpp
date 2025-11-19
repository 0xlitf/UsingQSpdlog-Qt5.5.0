
#include <QApplication>
#include "spdlog/spdlog.h"
#include "mainwindow.h"

int main(int argc, char **argv) {
    Q_INIT_RESOURCE(qspdlog_resources);

    QApplication app(argc, argv);

    MainWindow main;
    main.setMinimumSize(960, 720);
    main.show();

    int result = app.exec();
    spdlog::shutdown();

    return result;
}
