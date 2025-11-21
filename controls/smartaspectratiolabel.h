#ifndef SMARTASPECTRATIOLABEL_H
#define SMARTASPECTRATIOLABEL_H

#include <QLabel>
#include <QTimer>

class SmartAspectRatioLabel : public QLabel {
    Q_OBJECT
public:
    SmartAspectRatioLabel(QWidget *parent = nullptr);

    void setPixmap(const QPixmap &pixmap);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void fastUpdatePixmap();

    void finalUpdatePixmap();

private:
    QPixmap m_originalPixmap;
    QPixmap m_fastScaledPixmap;
    QPixmap m_finalScaledPixmap;
    QTimer *fastResizeTimer;
    QTimer *finalResizeTimer;
};

#endif // SMARTASPECTRATIOLABEL_H
