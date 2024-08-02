
#include "HWidget.h"
#include "QHBoxLayout"

wl::HWidget::HWidget(QWidget *parent) : QWidget(parent) {
    auto *ly = new QHBoxLayout();
    this->setLayout(ly);
    ly->setSpacing(0);
    ly->setMargin(0);
//    ly->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
}

void wl::HWidget::addWidget(QWidget *wid) {
    auto *ly = dynamic_cast<QHBoxLayout *>(this->layout());
    ly->insertWidget(ly->count(), wid);
}

void wl::HWidget::enterEvent(QEvent *event) {
    if (this->enterEventCB) {
        this->enterEventCB(event);
    }
    QWidget::enterEvent(event);
}

void wl::HWidget::leaveEvent(QEvent *event) {
    if (this->leaveEventCB) {
        this->leaveEventCB(event);
    }
    QWidget::leaveEvent(event);
}
