#include "DemoInputWidget.h"
#include "Input.h"
#include "magic_enum.hpp"
#include "Icon.h"
#include "Card.h"
#include "VWidget.h"
#include "Text.h"
#include "Divider.h"
#include "Br.h"
#include "Select.h"

DemoInputWidget::DemoInputWidget(QWidget *parent) : DemoContentWidget(parent) {

    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        wi->addWidget(new wl::Input());
        wi->addWidget(wl::Divider::createLeft("基本使用"));
        wi->addWidget(new wl::Text("基本的输入框"));
        this->layoutLeft_->addWidget(card);
    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);

        {
            auto input = new wl::Input();
            input->setAttrPrefix((QWidget *) (new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::FileAddOutlined))), Qt::gray)));

            input->setAttrSize(wl::GeneralAttrSize::large);
            input->setAttrPlaceholder("large size");
            wi->addWidget(input);
            wi->addWidget(new wl::Br(20));
        }

        {
            auto input = new wl::Input();
            input->setAttrPrefix((QWidget *) (new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::FileAddOutlined))), Qt::gray)));

            input->setAttrSize(wl::GeneralAttrSize::middle);
            input->setAttrPlaceholder("middle size");
            wi->addWidget(input);
            wi->addWidget(new wl::Br(20));
        }

        {
            auto input = new wl::Input();
            input->setAttrPrefix((QWidget *) (new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::FileAddOutlined))), Qt::gray)));
            input->setAttrSize(wl::GeneralAttrSize::small);
            input->setAttrPlaceholder("small size");
            wi->addWidget(input);
            wi->addWidget(new wl::Br(20));
        }


        wi->addWidget(wl::Divider::createLeft("三种大小"));
        wi->addWidget(new wl::Text("我们为 <Input /> 输入框定义了三种尺寸（大、默认、小），高度分别为 40px、32px 和 24px。"));
        this->layoutRight_->addWidget(card);
    }

    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        {
            auto *input = new wl::Input();
            input->setAttrPlaceholder("Outlined");
            wi->addWidget(input);
            wi->addWidget(new wl::Br(20));
        }
        {
            auto *input = new wl::Input();
            input->setAttrVariant(wl::InputAttrVariant::filled);
            input->setAttrPlaceholder("Filled");
            wi->addWidget(input);
            wi->addWidget(new wl::Br(20));
        }
        {
            auto *input = new wl::Input();
            input->setAttrVariant(wl::InputAttrVariant::borderless);
            input->setAttrPlaceholder("Borderless");
            wi->addWidget(input);
            wi->addWidget(new wl::Br(20));
        }
        wi->addWidget(wl::Divider::createLeft("变体"));
        wi->addWidget(new wl::Text("Input 形态变体。"));
        this->layoutLeft_->addWidget(card);
    }

    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);
        {
            auto *input = new wl::Input();
            wi->addWidget(input);
            wi->addWidget(new wl::Br(20));
        }
        {
            auto *input = new wl::Input();
            input->setAttrAddonBefore(new QLabel("https://"));
            input->setAttrAddonAfter(new QLabel(".com"));
            wi->addWidget(input);
            wi->addWidget(new wl::Br(20));
        }
        wi->addWidget(wl::Divider::createLeft("前置/后置标签"));
        wi->addWidget(new wl::Text("用于配置一些固定组合。"));

    }

}
