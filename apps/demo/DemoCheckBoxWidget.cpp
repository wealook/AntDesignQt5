
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

        wi->addWidget(new wl::CheckBox("CheckBox"));
        wi->addWidget(new wl::Br());
        wi->addWidget(new wl::CheckBox(""));
        wi->addWidget(new wl::Br());

        std::vector<wl::GeneralAttrOption> options;
        options.emplace_back("Apple", "Apple");
        options.emplace_back("Pear", "Pear");
        options.emplace_back("Orange", "Orange");
        options.emplace_back("Orange1", "Orange1");
        options.emplace_back("Orange2", "Orange2");
        options.emplace_back("Orange3", "Orange3");
        auto *group = new wl::CheckBoxGroup(options, std::vector<QString>());
        connect(group, &wl::CheckBoxGroup::onChange, this, [](const std::vector<QString> &attrValue) {
            for (const auto& it: attrValue) {
                LOG_INFO(it.toStdString())
            }
        });
        wi->addWidget(group);
        wi->addWidget(new wl::Br());
        wi->addWidget(wl::Divider::createLeft("基本用法"));
        wi->addWidget(new wl::Text("简单的 checkbox。"));

    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);

        {
            auto *box = new wl::CheckBox("CheckBox");
            box->setAttrDefaultChecked(false);
            box->setAttrIndeterminate(false);
            box->setAttrDisabled(true);
            wi->addWidget(box);
            wi->addWidget(new wl::Br());
        }
        {
            auto *box = new wl::CheckBox("CheckBox");
            box->setAttrDefaultChecked(false);
            box->setAttrIndeterminate(true);
            box->setAttrDisabled(true);
            wi->addWidget(box);
            wi->addWidget(new wl::Br());
        }
        {
            auto *box = new wl::CheckBox("CheckBox");
            box->setAttrDefaultChecked(true);
            box->setAttrIndeterminate(false);
            box->setAttrDisabled(true);
            wi->addWidget(box);
            wi->addWidget(new wl::Br());
        }

        wi->addWidget(wl::Divider::createLeft("不可用状态"));
        wi->addWidget(new wl::Text("checkbox 不可用。"));

    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);
        {
            auto *box = new wl::CheckBox("CheckBox");
            wi->addWidget(box);
            wi->addWidget(new wl::Br());
        }
        {
            auto *box = new wl::CheckBox("CheckBox");
            box->setAttrIndeterminate(true);
            wi->addWidget(box);
            wi->addWidget(new wl::Br());
        }
        {
            auto *box = new wl::CheckBox("CheckBox");
            box->setAttrDefaultChecked(true);
            wi->addWidget(box);
            wi->addWidget(new wl::Br());
        }
        wi->addWidget(wl::Divider::createLeft("三种情形"));
        wi->addWidget(new wl::Text("checkbox 。"));

    }
}
