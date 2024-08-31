#include "DemoSelectWidget.h"
#include "Select.h"
#include "VWidget.h"
#include "Card.h"
#include "Divider.h"
#include "Text.h"
#include "Button.h"
#include "Br.h"

DemoSelectWidget::DemoSelectWidget(QWidget *parent) : DemoContentWidget(parent) {
    auto options = wl::SelectAttrOptions();
    for (int index = 0; index < 10; index++) {
        options.emplace_back(
                QString("item中文" + QString::fromStdString(std::to_string(index))).toStdWString(),
                QString("item中文" + QString::fromStdString(std::to_string(index))).toStdWString()
        );
    }
    {
        auto *card = new wl::Card();
        auto *wi = new wl::VWidget();
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);
        {
            auto *pSelect = new wl::Select(wi);
            pSelect->setAttrSize(wl::GeneralAttrSize::small);
            pSelect->setAttrMode(wl::SelectAttrMode::none);
            pSelect->setAttrOptions(options);
            wi->addWidget(pSelect);
            wi->addWidget(new wl::Br(10));
        }
        {
            auto *pSelect = new wl::Select(wi);
            pSelect->setAttrSize(wl::GeneralAttrSize::middle);
            pSelect->setAttrMode(wl::SelectAttrMode::none);
            pSelect->setAttrOptions(options);
            wi->addWidget(pSelect);
            wi->addWidget(new wl::Br(10));
        }
        {
            auto *pSelect = new wl::Select(wi);
            pSelect->setAttrSize(wl::GeneralAttrSize::large);
            pSelect->setAttrMode(wl::SelectAttrMode::none);
            pSelect->setAttrOptions(options);
            wi->addWidget(pSelect);
        }
        wi->addWidget(wl::Divider::createLeft("基本使用"));
        wi->addWidget(new wl::Text("基本使用。"));
    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);
        {
            auto *pSelect = new wl::Select();
            pSelect->setAttrSize(wl::GeneralAttrSize::small);
            pSelect->setAttrOptions(options);
            wi->addWidget(pSelect);
            wi->addWidget(new wl::Br(10));
        }
        {
            auto *pSelect = new wl::Select();
            pSelect->setAttrSize(wl::GeneralAttrSize::middle);
            pSelect->setAttrOptions(options);
            wi->addWidget(pSelect);
            wi->addWidget(new wl::Br(10));
        }
        {
            auto *pSelect = new wl::Select();
            pSelect->setAttrSize(wl::GeneralAttrSize::large);
            pSelect->setAttrOptions(options);
            wi->addWidget(pSelect);
        }
        wi->addWidget(wl::Divider::createLeft("基本使用"));
        wi->addWidget(new wl::Text("基本使用。"));

    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);

        {
            auto *pSelect = new wl::Select(wi);
            pSelect->setAttrSize(wl::GeneralAttrSize::small);
            pSelect->setAttrOptions(options);
            pSelect->setAttrMode(wl::SelectAttrMode::tags);
            wi->addWidget(pSelect);
            wi->addWidget(new wl::Br(10));
        }
        {
            auto *pSelect = new wl::Select(wi);
            pSelect->setAttrSize(wl::GeneralAttrSize::middle);
            pSelect->setAttrOptions(options);
            pSelect->setAttrMode(wl::SelectAttrMode::tags);
            wi->addWidget(pSelect);
            wi->addWidget(new wl::Br(10));
        }
        {
            auto *pSelect = new wl::Select(wi);
            pSelect->setAttrSize(wl::GeneralAttrSize::large);
            pSelect->setAttrOptions(options);
            pSelect->setAttrMode(wl::SelectAttrMode::tags);
            wi->addWidget(pSelect);
        }

        wi->addWidget(wl::Divider::createLeft("基本使用"));
        wi->addWidget(new wl::Text("tags"));
    }
}
