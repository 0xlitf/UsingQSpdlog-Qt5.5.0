#ifndef MEMORYMONITORWIDGET_H
#define MEMORYMONITORWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>

class MemoryMonitorWidget : public QWidget {
    Q_OBJECT

public:
    explicit MemoryMonitorWidget(QWidget* parent = nullptr);

private slots:
    void updateMemoryUsage();

private:
    QLabel* m_memoryLabel;
    QLabel* m_virtualMemoryLabel;
    QLabel* m_peakMemoryLabel;
    QTimer* m_updateTimer;

    qint64 m_peakMemoryUsage = 0;
};

#endif // MEMORYMONITORWIDGET_H
