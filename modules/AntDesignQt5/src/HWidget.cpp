
#include "HWidget.h"
#include "QHBoxLayout"

wl::HWidget::HWidget(QWidget *parent) : QWidget(parent) {
    auto *ly = new QHBoxLayout();
    this->setLayout(ly);
    ly->setSpacing(0);
    ly->setMargin(0);
    ly->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
}

void wl::HWidget::addWidget(QWidget *wid) {
    auto *ly = dynamic_cast<QHBoxLayout *>(this->layout());
    ly->insertWidget(ly->count(), wid);
}
