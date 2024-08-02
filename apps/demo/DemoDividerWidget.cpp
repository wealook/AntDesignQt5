//
///7/10.
//

#include "DemoDividerWidget.h"
#include "QPushButton"
#include "QDateTimeEdit"
#include "Divider.h"

DemoDividerWidget::DemoDividerWidget(QWidget *parent) : DemoContentWidget(parent) {
    this->layoutLeft_->addWidget(new QPushButton("bt1"));
    this->layoutLeft_->addWidget(new wl::Divider(wl::DividerAttr(wl::GeneralAttrTypeDirection::vertical)));
    this->layoutLeft_->addWidget(new wl::Divider(wl::DividerAttr()));

    this->layoutLeft_->addWidget(new wl::Divider(wl::DividerAttr("Text", wl::DividerAttrOrientation::left)));
    this->layoutLeft_->addWidget(new wl::Divider(wl::DividerAttr("Text", wl::DividerAttrOrientation::center)));
    this->layoutLeft_->addWidget(new wl::Divider(wl::DividerAttr("Text", wl::DividerAttrOrientation::right)));
    this->layoutLeft_->addWidget(new wl::Divider(wl::DividerAttr(new QPushButton("hahha"), wl::DividerAttrOrientation::left)));
    this->layoutLeft_->addWidget(new wl::Divider(wl::DividerAttr(new QPushButton("hahha"), wl::DividerAttrOrientation::center)));
    this->layoutLeft_->addWidget(new wl::Divider(wl::DividerAttr(new QPushButton("hahha"), wl::DividerAttrOrientation::right)));
    this->layoutLeft_->addWidget(new QPushButton("bt2"));

}
