//
///7/10.
//

#include "DemoDividerWidget.h"
#include "QPushButton"
#include "QDateTimeEdit"
#include "Divider.h"

DemoDividerWidget::DemoDividerWidget(QWidget *parent) : DemoContentWidget(parent) {
//    this->layoutLeft_->addWidget(new QPushButton("bt1"));
    auto *divider = new wl::Divider(true);
    divider->setMaximumHeight(60);
    this->layoutLeft_->addWidget(divider);
    this->layoutLeft_->addWidget(new wl::Divider());

    this->layoutLeft_->addWidget(new wl::Divider("Text", wl::DividerAttrOrientation::left));
    this->layoutLeft_->addWidget(new wl::Divider("Text", wl::DividerAttrOrientation::center));
    this->layoutLeft_->addWidget(new wl::Divider("Text", wl::DividerAttrOrientation::right));
    this->layoutLeft_->addWidget(new wl::Divider(new QPushButton(u8"\u4E2D\u6587"), wl::DividerAttrOrientation::left));
    this->layoutLeft_->addWidget(new wl::Divider(new QPushButton(u8"\u4E2D\u6587"), wl::DividerAttrOrientation::center));
    this->layoutLeft_->addWidget(new wl::Divider(new QPushButton(u8"\u4E2D\u6587"), wl::DividerAttrOrientation::right));
//    this->layoutLeft_->addWidget(new QPushButton("bt2"));

}
