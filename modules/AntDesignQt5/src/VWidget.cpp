#include "VWidget.h"
#include "QVBoxLayout"

wl::VWidget::VWidget(QWidget *parent) : QWidget(parent) {
    auto *ly = new QVBoxLayout();
    this->setLayout(ly);
    ly->setSpacing(0);
    ly->setMargin(0);
    ly->setAlignment(Qt::AlignTop);

//    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//    ly->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));
    this->setStyleSheet("border:none;");
//    this->setStyleSheet("border:1px solid green;");
}

void wl::VWidget::addWidget(QWidget *wid) {
//    wid->setParent(this);
    auto *ly = dynamic_cast<QVBoxLayout *>(this->layout());
    ly->insertWidget(ly->count(), wid);
}
