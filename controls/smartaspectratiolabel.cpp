#include "smartaspectratiolabel.h"

SmartAspectRatioLabel::SmartAspectRatioLabel(QWidget *parent) : QLabel(parent) {
    setAlignment(Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    fastResizeTimer = new QTimer(this);
    fastResizeTimer->setSingleShot(true);
    fastResizeTimer->setInterval(16); // 约60fps

    finalResizeTimer = new QTimer(this);
    finalResizeTimer->setSingleShot(true);
    finalResizeTimer->setInterval(200); // 200ms后最终缩放

    connect(fastResizeTimer, &QTimer::timeout, this, &SmartAspectRatioLabel::fastUpdatePixmap);
    connect(finalResizeTimer, &QTimer::timeout, this, &SmartAspectRatioLabel::finalUpdatePixmap);
}

void SmartAspectRatioLabel::setPixmap(const QPixmap &pixmap) {
    m_originalPixmap = pixmap;
    m_fastScaledPixmap = QPixmap();
    m_finalScaledPixmap = QPixmap();
    finalUpdatePixmap();
}

void SmartAspectRatioLabel::resizeEvent(QResizeEvent *event) {
    QLabel::resizeEvent(event);

    // 停止之前的计时器
    finalResizeTimer->stop();

    // 先快速缩放
    fastResizeTimer->start();
    // 延迟最终高质量缩放
    finalResizeTimer->start();
}

void SmartAspectRatioLabel::fastUpdatePixmap() {
    if (m_originalPixmap.isNull()) return;

    // 快速缩放（低质量）
    QPixmap fastScaled = m_originalPixmap.scaled(
                this->size(),
                Qt::KeepAspectRatio,
                Qt::FastTransformation
                );

    // 只有当尺寸不同时才更新
    if (fastScaled.size() != m_fastScaledPixmap.size()) {
        m_fastScaledPixmap = fastScaled;
        QLabel::setPixmap(m_fastScaledPixmap);
    }
}

void SmartAspectRatioLabel::finalUpdatePixmap() {
    if (m_originalPixmap.isNull()) return;

    // 高质量缩放
    QPixmap finalScaled = m_originalPixmap.scaled(
                this->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
                );

    // 只有当尺寸不同时才更新
    if (finalScaled.size() != m_finalScaledPixmap.size()) {
        m_finalScaledPixmap = finalScaled;
        QLabel::setPixmap(m_finalScaledPixmap);
    }
}
