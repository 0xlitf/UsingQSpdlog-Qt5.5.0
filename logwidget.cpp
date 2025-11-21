#include "logwidget.h"
#include "controls/controls.h"
#include <memory>
#include <thread>
#include "logger.h"

LogWidget::LogWidget(QWidget *parent) : WidgetBase(parent) {
    this->createComponent();
}

void LogWidget::createComponent() {
    using namespace Layouting;

    auto m_centralTop = [=]() {
        WidgetBase *w = new WidgetBase();
        w->setBackgroundColor(QColor("#dddddd"));
        w->setFixedHeight(50);
        w->setContentsMargins(0, 0, 0, 0);
        return w;
    }();
    auto m_centralCenter = [=]() {
        auto *w = new QSpdLog();


        return w;
    }();

    Column {m_centralTop, m_centralCenter}.attachTo(this);
}
