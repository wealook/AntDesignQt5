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
        auto attr = wl::InputAttr();
//    attr.prefix = (QWidget *) (new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::UsergroupAddOutlined))), Qt::gray));
//    attr.suffix = (QWidget *) (new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::SearchOutlined))), Qt::blue));
        wi->addWidget(new wl::Input(attr));
        wi->addWidget(wl::Divider::createLeft("基本使用"));
        wi->addWidget(new wl::Text("基本的输入框"));
        this->layoutLeft_->addWidget(card);
    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        auto attr = wl::InputAttr();
        attr.prefix = (QWidget *) (new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::FileAddOutlined))), Qt::gray));
        attr.size = wl::GeneralAttrSize::large;
        attr.placeholder = "large size";
        wi->addWidget(new wl::Input(attr));
        wi->addWidget(new wl::Br(20));

        attr.size = wl::GeneralAttrSize::middle;
        attr.placeholder = "middle size";
        attr.prefix = (QWidget *) (new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::FileAddOutlined))), Qt::gray));
        wi->addWidget(new wl::Input(attr));
        wi->addWidget(new wl::Br(20));

        attr.size = wl::GeneralAttrSize::small;
        attr.placeholder = "small size";
        attr.prefix = (QWidget *) (new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::FileAddOutlined))), Qt::gray));
        wi->addWidget(new wl::Input(attr));
        wi->addWidget(wl::Divider::createLeft("三种大小"));
        wi->addWidget(new wl::Text("我们为 <Input /> 输入框定义了三种尺寸（大、默认、小），高度分别为 40px、32px 和 24px。"));
        this->layoutRight_->addWidget(card);
    }

    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        auto attr = wl::InputAttr();
        attr.placeholder = "Outlined";
        wi->addWidget(new wl::Input(attr));
        wi->addWidget(new wl::Br());

        attr.variant = wl::InputAttrVariant::filled;
        attr.placeholder = "Filled";
        wi->addWidget(new wl::Input(attr));
        wi->addWidget(new wl::Br());

        attr.variant = wl::InputAttrVariant::borderless;
        attr.placeholder = "Borderless";
        wi->addWidget(new wl::Input(attr));


        wi->addWidget(wl::Divider::createLeft("变体"));
        wi->addWidget(new wl::Text("Input 形态变体。"));
        this->layoutLeft_->addWidget(card);
    }

    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
//        wi->setMaximumWidth(400);
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);

        auto attr = wl::InputAttr();
        attr.prefix = nullptr;
        wi->addWidget(new wl::Input(attr));
        wi->addWidget(new wl::Br());

        wi->addWidget(new wl::Input(attr));
        wi->addWidget(new wl::Br());

        attr.addonBefore = new QLabel("https://");
        attr.addonAfter = new QLabel(".com");
        wi->addWidget(new wl::Input(attr));


        wi->addWidget(wl::Divider::createLeft("前置/后置标签"));
        wi->addWidget(new wl::Text("用于配置一些固定组合。"));

    }

}
