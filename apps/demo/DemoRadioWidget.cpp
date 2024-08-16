
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

        wi->addWidget(new wl::Radio(wl::RadioAttr("Radio")));

        wi->addWidget(new wl::Br());
        wi->addWidget(new wl::Radio(wl::RadioAttr("")));
        wi->addWidget(new wl::Br());

        auto groupAttr = wl::RadioGroupAttr();
        std::vector<wl::GeneralAttrOption> options;
        options.emplace_back("Apple", "Apple");
        options.emplace_back("Pear", "Pear");
        options.emplace_back("Orange", "Orange");
        groupAttr.options = options;
        wi->addWidget(new wl::RadioGroup(groupAttr));
        wi->addWidget(new wl::Br());

        wi->addWidget(wl::Divider::createLeft("基本用法"));
        wi->addWidget(new wl::Text("简单的 Radio。"));

    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);

        wi->addWidget(new wl::Radio(wl::RadioAttr("", false, true)));
        wi->addWidget(new wl::Br());
        wi->addWidget(new wl::Radio(wl::RadioAttr("", true, true)));

        wi->addWidget(wl::Divider::createLeft("不可用状态"));
        wi->addWidget(new wl::Text("Radio 不可用。"));

    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);

        wi->addWidget(new wl::Radio(wl::RadioAttr("", false, false)));
        wi->addWidget(new wl::Br());
        wi->addWidget(new wl::Radio(wl::RadioAttr("", true, false)));

        wi->addWidget(wl::Divider::createLeft("两种情形"));
        wi->addWidget(new wl::Text("Radio 。"));

    }
}
