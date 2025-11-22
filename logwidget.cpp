#include "logwidget.h"
#include <QAction>
#include "controls/controls.h"
#include "logger.h"
#include <memory>
#include <thread>

LogWidget::LogWidget(QWidget *parent) : QMainWindow(parent) {
    m_logger = createLogger("main");

    this->setCentralWidget(central);

    this->createAction();
    this->createComponent();

    m_logger->sinks().push_back(m_logView->sink());
}

void LogWidget::createComponent() {
    using namespace Layouting;

    auto addLogButton = new NormalButton(this);
    addLogButton->setText("addLog");
    addLogButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // addLogButton->setFixedSize(50, 30);
    connect(addLogButton, &QPushButton::clicked, m_generateAction, &QAction::triggered);

    auto addThreadLogButton = new NormalButton(this);
    addThreadLogButton->setText("addThreadLog");
    addThreadLogButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(addThreadLogButton,
            &QPushButton::clicked,
            m_generateMultipleAction,
            &QAction::triggered);

    auto clearButton = new NormalButton(this);
    clearButton->setText("clear");
    clearButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(clearButton, &QPushButton::clicked, m_clearAction, &QAction::triggered);

    auto lineEdit = new LineEdit(this);
    lineEdit->setText("Test");
    // lineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // lineEdit->setFixedSize(100, 35);

    auto Aa = new NormalButton(this);
    Aa->setFixedSize(35, 35);
    Aa->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Aa->setText("Aa");
    Aa->setCheckable(true);

    auto regex = new NormalButton(this);
    regex->setFixedSize(35, 35);
    regex->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    regex->setText(".*");
    regex->setCheckable(true);
    auto m_centralTop = [=]() {
        WidgetBase *w = new WidgetBase();
        w->setBackgroundColor(QColor("#dddddd"));
        w->setFixedHeight(150);
        // w->setContentsMargins(0, 0, 0, 0);

        Column{Row{addLogButton, addThreadLogButton, clearButton, Stretch()},
               Row{lineEdit, Aa, regex, Stretch()}}
            .attachTo(w);

        return w;
    }();
    m_logView = new QSpdLog();

    Column{m_centralTop, m_logView}.attachTo(central);
}

void LogWidget::createAction() {
    m_clearAction = new QAction("Clear", this);
    m_generateAction = new QAction("Generate", this);
    m_generateMultipleAction = new QAction("GenerateMultiple", this);

    m_generateAction->connect(m_generateAction, &QAction::triggered, this, [this](bool) {
        // generate 10 messages with random levels
        for (int i = 0; i < 10; ++i)
            m_logger->log(static_cast<spdlog::level::level_enum>(rand() % spdlog::level::off),
                          "Message {}",
                          i);
    });

    m_generateMultipleAction
        ->connect(m_generateMultipleAction, &QAction::triggered, this, [this](bool) {
            // create 10 threads and generate 10 messages with random levels
            std::vector<std::thread> threads;
            for (int i = 0; i < 10; ++i) {
                threads.emplace_back([this, i]() {
                    auto threadLocalLogger = createLogger(fmt::format("thread {}", i));
                    threadLocalLogger->sinks().push_back(m_logView->sink());
                    m_logger->info("Thread {} started", i);
                    for (int j = 0; j < 10; ++j) {
                        threadLocalLogger->log(static_cast<spdlog::level::level_enum>(
                                                   rand() % spdlog::level::off),
                                               "Message {}",
                                               j);
                    }
                    m_logger->info("Thread {} finished", i);
                });
            }

            for (auto &thread : threads)
                thread.join();
        });

    m_clearAction->connect(m_clearAction, &QAction::triggered, this, [this](bool) {
        m_logView->clear();
    });
}
