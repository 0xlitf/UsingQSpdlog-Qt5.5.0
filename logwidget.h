#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include "controls/widgetbase.h"
#include <memory>
#include <QMainWindow>
#include "spdlog/spdlog.h"

class LogWidget: public QMainWindow {
public:
    LogWidget(QWidget* parent = nullptr);
    void createComponent();
    void createAction();

private:
    std::shared_ptr<spdlog::logger> m_logger;
    class QSpdLog* m_logView;
    QAction *m_clearAction;
    QAction *m_generateAction;
    QAction *m_generateMultipleAction;

    WidgetBase* central = new WidgetBase;
};

#endif // LOGWIDGET_H
