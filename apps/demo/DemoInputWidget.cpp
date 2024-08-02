#include "DemoInputWidget.h"
#include "Input.h"
#include "magic_enum.hpp"
#include "Icon.h"

DemoInputWidget::DemoInputWidget(QWidget *parent) : DemoContentWidget(parent) {
    auto attr = wl::InputAttr();
    attr.prefix = (QWidget *) (new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::SearchOutlined))), Qt::gray));
//    attr.suffix = (QWidget *) (new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::SearchOutlined))), Qt::blue));
    this->layoutLeft_->addWidget(new wl::Input(attr));
    attr.prefix = nullptr;
    attr.size = wl::GeneralAttrSize::large;
    this->layoutLeft_->addWidget(new wl::Input(attr));
    attr.size = wl::GeneralAttrSize::small;
    this->layoutLeft_->addWidget(new wl::Input(attr));
    this->layoutLeft_->addWidget(new wl::Input(wl::InputAttr("http://", "")));
}
