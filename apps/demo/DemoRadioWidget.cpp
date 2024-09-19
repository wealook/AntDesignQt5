
#include "DemoRadioWidget.h"
#include "Radio.h"
#include "VWidget.h"
#include "Card.h"
#include "Br.h"
#include "Divider.h"
#include "Text.h"

DemoRadioWidget::DemoRadioWidget(QWidget *parent) : DemoContentWidget(parent) {
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);

        {
            auto *radio = new wl::Radio("Radio");
            wi->addWidget(radio);
            wi->addWidget(new wl::Br());
        }
        {
            auto *radio = new wl::Radio("");
            wi->addWidget(radio);
            wi->addWidget(new wl::Br());
        }


        std::vector<wl::GeneralAttrOption> options;
        options.emplace_back("Apple", "Apple");
        options.emplace_back("Pear", "Pear");
        options.emplace_back("Orange", "Orange");
        wi->addWidget(new wl::RadioGroup(options, "", this));
        wi->addWidget(new wl::Br());
        wi->addWidget(wl::Divider::createLeft("基本用法"));
        wi->addWidget(new wl::Text("简单的 Radio。"));

    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);

        {
            auto *radio = new wl::Radio("Radio");
            radio->setAttrDefaultChecked(true);
            radio->setAttrDisabled(true);
            wi->addWidget(radio);
            wi->addWidget(new wl::Br());
        }

        {
            auto *radio = new wl::Radio("Radio");
            radio->setAttrDefaultChecked(false);
            radio->setAttrDisabled(true);
            wi->addWidget(radio);
            wi->addWidget(new wl::Br());
        }

        wi->addWidget(wl::Divider::createLeft("不可用状态"));
        wi->addWidget(new wl::Text("Radio 不可用。"));

    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);

        {
            auto *radio = new wl::Radio("Radio");
            radio->setAttrDefaultChecked(true);
            radio->setAttrDisabled(false);
            wi->addWidget(radio);
            wi->addWidget(new wl::Br());
        }

        {
            auto *radio = new wl::Radio("Radio");
            radio->setAttrDefaultChecked(false);
            radio->setAttrDisabled(false);
            wi->addWidget(radio);
            wi->addWidget(new wl::Br());
        }

        wi->addWidget(wl::Divider::createLeft("两种情形"));
        wi->addWidget(new wl::Text("Radio 。"));

    }
}
