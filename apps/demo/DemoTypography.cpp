#include "DemoTypography.h"
#include "Card.h"
#include "QLayout"
#include "VWidget.h"
#include "Title.h"
#include "Text.h"

DemoTypography::DemoTypography(QWidget *parent) : QWidget(parent) {
    auto *ly = new QVBoxLayout();
    this->setLayout(ly);
    {
        auto *card = new wl::Card();
        auto *vWidget = new wl::VWidget();
        vWidget->addWidget(new wl::Title("h1. Ant Design", 1));
        vWidget->addWidget(new wl::Title("h2. Ant Design", 2));
        vWidget->addWidget(new wl::Title("h3. Ant Design", 3));
        vWidget->addWidget(new wl::Title("h4. Ant Design", 4));
        vWidget->addWidget(new wl::Title("h5. Ant Design", 5));
        card->setContentWidget(vWidget);
        ly->addWidget(card);
    }
    {
        auto *card = new wl::Card();
        auto *vWidget = new wl::VWidget();
        auto *text = new wl::Text("Ant Design (default)");
        text->setAttr(wl::TextAttr());
        vWidget->addWidget(text);
        vWidget->addWidget(new wl::Text("Ant Design (secondary)", wl::TextAttr(wl::GeneralAttrColorType::secondary)));
        vWidget->addWidget(new wl::Text("Ant Design (success)", wl::TextAttr(wl::GeneralAttrColorType::success)));
        vWidget->addWidget(new wl::Text("Ant Design (warning)", wl::TextAttr(wl::GeneralAttrColorType::warning)));
        vWidget->addWidget(new wl::Text("Ant Design (danger)", wl::TextAttr(wl::GeneralAttrColorType::danger)));
        {
            auto attr = wl::TextAttr(wl::GeneralAttrColorType::none);
            attr.mark = true;
            vWidget->addWidget(new wl::Text("Ant Design (underline)", attr));
        }
        {
            auto attr = wl::TextAttr(wl::GeneralAttrColorType::none);
            attr.code = true;
            vWidget->addWidget(new wl::Text("Ant Design (underline)", attr));
        }
        {
            auto attr = wl::TextAttr(wl::GeneralAttrColorType::none);
            attr.keyboard = true;
            vWidget->addWidget(new wl::Text("Ant Design (underline)", attr));
        }
        {
            auto attr = wl::TextAttr(wl::GeneralAttrColorType::none);
            attr.underline = true;
            vWidget->addWidget(new wl::Text("Ant Design (underline)", attr));
        }
        {
            auto attr = wl::TextAttr(wl::GeneralAttrColorType::none);
            attr.destroy = true;
            vWidget->addWidget(new wl::Text("Ant Design (destroy)", attr));
        }
        {
            auto attr = wl::TextAttr(wl::GeneralAttrColorType::none);
            attr.strong = true;
            vWidget->addWidget(new wl::Text("Ant Design (strong)", attr));
        }
        {
            auto attr = wl::TextAttr(wl::GeneralAttrColorType::none);
            attr.italic = true;
            vWidget->addWidget(new wl::Text("Ant Design (italic)", attr));
        }
        {
            auto attr = wl::TextAttr(wl::GeneralAttrColorType::none);
            attr.link = true;
            vWidget->addWidget(new wl::Text("Ant Design (link)", attr));
        }
        card->setContentWidget(vWidget);
        ly->addWidget(card);
    }
}
