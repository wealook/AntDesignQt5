#include "DemoFlexWidget.h"
#include "Flex.h"
#include "VWidget.h"
#include "Card.h"
#include "Divider.h"
#include "Input.h"
#include "Tag.h"
#include "QLineEdit"
#include "Button.h"

DemoFlexWidget::DemoFlexWidget(QWidget *parent) : DemoContentWidget(parent) {

//    {
//        auto *wi = new wl::VWidget();
//        auto *card = new wl::Card();
//        card->setContentWidget(wi);
//        this->layoutLeft_->addWidget(card);
//        auto *flex = new wl::Flex();
//        for (int index = 0; index < 10; index++) {
//            flex->addWidget(new wl::Text("Flex"));
//        }
//        wi->addWidget(flex);
//        wi->addWidget(wl::Divider::createLeft("基本使用"));
//        wi->addWidget(new wl::Text("基本使用。"));
//    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);
        auto *flex = new wl::Flex();
        for (int index = 0; index < 15; index++) {
            auto *tag = new wl::Tag("中文TAG");
            tag->setMinimumHeight(28);
            flex->addWidget(tag);
        }

        auto *btn = new wl::Button("添加TAG", this);
        btn->setAttrType(wl::ButtonAttrType::primary);
        btn->setAttrSize(wl::GeneralAttrSize::middle);
        btn->setAttrShape(wl::GeneralAttrShape::round);
        connect(btn, &wl::Button::clicked, this, [flex]() {
            auto *tag = new wl::Tag("中文TAG");
            tag->setMinimumHeight(28);
            flex->addWidget(tag);
        });

        wi->addWidget(btn);
        wi->addWidget(flex);
//        wi->addWidget(hwi);
        wi->addWidget(wl::Divider::createLeft("基本使用"));
        wi->addWidget(new wl::Text("基本使用。"));
    }
}
