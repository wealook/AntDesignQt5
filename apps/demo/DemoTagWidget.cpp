
#include "DemoTagWidget.h"
#include "Card.h"
#include "Divider.h"
#include "Text.h"
#include "VWidget.h"
#include "Tag.h"
#include "Br.h"
#include "Icon.h"
#include "Util.h"

DemoTagWidget::DemoTagWidget(QWidget *parent) : DemoContentWidget(parent) {
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
//        wi->setMaximumWidth(400);
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);


        auto *tag = new wl::Tag("中文Tag", this);

        wi->addWidget(new wl::Br());
        wi->addWidget(tag);
        wi->addWidget(new wl::Br());
        {
            auto tag1 = new wl::Tag("中文Tag", this);
            tag1->setAttrColor(wl::GeneralAttrColorType::success);
            wi->addWidget(tag1);
        }
        wi->addWidget(new wl::Br());
        {
            auto tag1 = new wl::Tag("中文Tag", this);
            tag1->setAttrColor(wl::GeneralAttrColorType::processing);
            wi->addWidget(tag1);
        }
        wi->addWidget(new wl::Br());
        {
            auto tag1 = new wl::Tag("中文Tag", this);
            tag1->setAttrColor(wl::GeneralAttrColorType::warning);
            tag1->setAttrIcon(new wl::Icon("CloseOutlined", tag1->getPrimaryColor()));
            wi->addWidget(tag1);
        }
        wi->addWidget(new wl::Br());

        {
            auto tag1 = new wl::Tag("中文Tag", this);
            tag1->setAttrColor(wl::GeneralAttrColorType::error);
            tag1->setAttrCloseIcon(new wl::Icon("CloseOutlined", tag1->getPrimaryColor()));
            connect(tag1, &wl::Tag::closed, this, []() {
                LOG_WARN("onclose clicked")
            });
            wi->addWidget(tag1);
        }
        wi->addWidget(new wl::Br());

        wi->addWidget(wl::Divider::createLeft("基本使用"));
        wi->addWidget(new wl::Text("各种颜色"));

    }
}
