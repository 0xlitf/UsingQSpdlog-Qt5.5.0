#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include "controls/widgetbase.h"

class LogWidget: public WidgetBase {
public:
    LogWidget(QWidget* parent = nullptr);
    void createComponent();
};

#endif // LOGWIDGET_H
