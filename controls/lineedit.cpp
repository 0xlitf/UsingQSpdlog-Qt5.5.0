#include "lineedit.h"
#include <QPainter>
#include <QAction>
#include <QIcon>
#include <QPainterPath>

LineEdit::LineEdit(QWidget* parent)
    : QLineEdit(parent) {
    this->setMinimumSize(50, 35);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, Qt::transparent);
    palette.setColor(QPalette::Text, QColor("#222222"));

    this->setPalette(palette);
    this->setFrame(false);

    this->setupActions();
}

void LineEdit::setBorderColor(const QColor& color) {
    m_borderColor = color;
    update();
}

void LineEdit::setBorderWidth(int width) {
    m_borderWidth = width;
    update();
}

void LineEdit::setCornerRadius(int radius) {
    m_cornerRadius = radius;
    update();
}

void LineEdit::setupActions() {
    m_settingsAction = new QAction(QIcon(":/image/delete.svg"), "", this);
    connect(m_settingsAction, &QAction::triggered, this, [this]() { this->setText(""); });

    updateActionVisibility();
}

void LineEdit::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect bgRect = rect().adjusted(m_borderWidth, m_borderWidth, -m_borderWidth, -m_borderWidth);
    painter.setBrush(palette().base());
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(bgRect, m_cornerRadius, m_cornerRadius);

    QPen borderPen(m_borderColor, m_borderWidth);
    painter.setPen(borderPen);
    if (this->hasFocus()) {
        painter.setBrush(Qt::white);
    } else {
        painter.setBrush(Qt::NoBrush);
    }
    painter.drawRoundedRect(rect().adjusted(0, 0, 0, 0), m_cornerRadius, m_cornerRadius);

    drawFocusIndicator(painter);

    QRect textRect = rect().adjusted(8, 2, -25, -2);
    painter.setClipRect(textRect);

    QLineEdit::paintEvent(event);
}

void LineEdit::drawFocusIndicator(QPainter& painter) {
    painter.save();

    QPainterPath maskPath;
    maskPath.addRoundedRect(rect(), m_cornerRadius, m_cornerRadius);

    painter.setClipPath(maskPath);

    QColor lineColor = this->hasFocus() ? QColor("#005a9e") : QColor("#999999");
    int lineHeight = this->hasFocus() ? 3 : 2;

    int lineY = rect().height() - lineHeight;
    painter.setPen(Qt::NoPen);
    painter.setBrush(lineColor);
    painter.drawRect(0, lineY, rect().width(), lineHeight);

    painter.restore();
}
