#include "memorymonitorwidget.h"
#include <windows.h>
#include <psapi.h>
#include <QHBoxLayout>

MemoryMonitorWidget::MemoryMonitorWidget(QWidget* parent)
    : QWidget(parent) {

    auto* layout = new QVBoxLayout(this);

    m_memoryLabel = new QLabel("Memory: --", this);
    m_virtualMemoryLabel = new QLabel("Virtual Memory: --", this);
    m_peakMemoryLabel = new QLabel("Peak Memory: --", this);

    layout->addWidget(m_memoryLabel);
    layout->addWidget(m_virtualMemoryLabel);
    layout->addWidget(m_peakMemoryLabel);

    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &MemoryMonitorWidget::updateMemoryUsage);
    m_updateTimer->start(1000);

    updateMemoryUsage();
}

void MemoryMonitorWidget::updateMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {

        qint64 currentMemory = pmc.WorkingSetSize;
        qint64 virtualMemory = pmc.PagefileUsage;

        if (currentMemory > m_peakMemoryUsage) {
            m_peakMemoryUsage = currentMemory;
        }

        auto formatMemory = [](qint64 bytes) -> QString {
            const qint64 MB = 1024 * 1024;
            return QString("%1 MB").arg(bytes / (double)MB, 0, 'f', 2);
        };

        m_memoryLabel->setText(QString("Memory: %1").arg(formatMemory(currentMemory)));
        m_virtualMemoryLabel->setText(QString("Virtual Memory: %1").arg(formatMemory(virtualMemory)));
        m_peakMemoryLabel->setText(QString("Peak Memory: %1").arg(formatMemory(m_peakMemoryUsage)));
    }
}
