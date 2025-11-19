#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "qspdlog/qspdlog.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QToolBar* m_toolbar = new QToolBar("Manipulation toolbar");
    QSpdLog* m_spdlogWidget = new QSpdLog();
};
#endif // MAINWINDOW_H
