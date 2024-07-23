#include "VWidget.h"
#include "QVBoxLayout"

wl::VWidget::VWidget(QWidget *parent) : QWidget(parent) {
    auto *ly = new QVBoxLayout();
    this->setLayout(ly);
    ly->setSpacing(0);
    ly->setMargin(0);
    ly->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
    this->setStyleSheet("border:none;");
}

void wl::VWidget::addWidget(QWidget *wid) {
    auto *ly = dynamic_cast<QVBoxLayout *>(this->layout());
    ly->insertWidget(ly->count(), wid);
}
