
#include "DemoCheckBoxWidget.h"
#include "CheckBox.h"
#include "VWidget.h"
#include "Card.h"
#include "Br.h"
#include "Divider.h"
#include "Text.h"

DemoCheckBoxWidget::DemoCheckBoxWidget(QWidget *parent) : DemoContentWidget(parent) {
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);

        wi->addWidget(new wl::CheckBox(wl::CheckBoxAttr("CheckBox")));

        wi->addWidget(new wl::Br());
        wi->addWidget(new wl::CheckBox(wl::CheckBoxAttr("")));
        wi->addWidget(new wl::Br());

        auto groupAttr = wl::CheckBoxGroupAttr();
        std::vector<wl::GeneralAttrOption> options;
        options.emplace_back("Apple", "Apple");
        options.emplace_back("Pear", "Pear");
        options.emplace_back("Orange", "Orange");
        groupAttr.options = options;
        wi->addWidget(new wl::CheckBoxGroup(groupAttr));
        wi->addWidget(new wl::Br());

        wi->addWidget(wl::Divider::createLeft("基本用法"));
        wi->addWidget(new wl::Text("简单的 checkbox。"));

    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);

        wi->addWidget(new wl::CheckBox(wl::CheckBoxAttr("", false, false, true)));
        wi->addWidget(new wl::Br());
        wi->addWidget(new wl::CheckBox(wl::CheckBoxAttr("", false, true, true)));
        wi->addWidget(new wl::Br());
        wi->addWidget(new wl::CheckBox(wl::CheckBoxAttr("", true, false, true)));

        wi->addWidget(wl::Divider::createLeft("不可用状态"));
        wi->addWidget(new wl::Text("checkbox 不可用。"));

    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);

        wi->addWidget(new wl::CheckBox(wl::CheckBoxAttr("", false, false, false)));
        wi->addWidget(new wl::Br());
        wi->addWidget(new wl::CheckBox(wl::CheckBoxAttr("", false, true, false)));
        wi->addWidget(new wl::Br());
        wi->addWidget(new wl::CheckBox(wl::CheckBoxAttr("", true, false, false)));

        wi->addWidget(wl::Divider::createLeft("三种情形"));
        wi->addWidget(new wl::Text("checkbox 。"));

    }
}
