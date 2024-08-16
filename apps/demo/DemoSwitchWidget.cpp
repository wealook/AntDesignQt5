#include "DemoSwitchWidget.h"
#include "Switch.h"
#include "VWidget.h"
#include "Card.h"
#include "Br.h"
#include "Divider.h"
#include "Text.h"

DemoSwitchWidget::DemoSwitchWidget() {
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);
        {
            auto attr = wl::SwitchAttr();
            attr.checked = true;
            wi->addWidget(new wl::Switch(attr));
            wi->addWidget(new wl::Br());
            attr.disabled = true;
            wi->addWidget(new wl::Switch(attr));
            wi->addWidget(new wl::Br());
            attr.disabled = false;
            attr.checkedChildren = new wl::Text("打开");
            attr.unCheckedChildren = new wl::Text("关闭");
            wi->addWidget(new wl::Switch(attr));
        }
        {
            auto attr = wl::SwitchAttr();
            attr.checked = false;
            wi->addWidget(new wl::Switch(attr));
            wi->addWidget(new wl::Br());
            attr.disabled = true;
            wi->addWidget(new wl::Switch(attr));
            wi->addWidget(new wl::Br());
        }
        {
            auto attr = wl::SwitchAttr();
            attr.size = wl::GeneralAttrSize::small;
            attr.checked = false;
            wi->addWidget(new wl::Switch(attr));
            wi->addWidget(new wl::Br());
            attr.disabled = true;
            wi->addWidget(new wl::Switch(attr));
            wi->addWidget(new wl::Br());
        }
        {
            auto attr = wl::SwitchAttr();
            attr.size = wl::GeneralAttrSize::small;
            attr.checked = false;
            wi->addWidget(new wl::Switch(attr));
            wi->addWidget(new wl::Br());
            attr.checked = true;
            attr.checkedChildren = new wl::Text("打开");
            attr.unCheckedChildren = new wl::Text("关闭");
            wi->addWidget(new wl::Switch(attr));
            wi->addWidget(new wl::Br());
        }
        wi->addWidget(wl::Divider::createLeft("基本用法"));
        wi->addWidget(new wl::Text("最简单的用。"));

    }
}
