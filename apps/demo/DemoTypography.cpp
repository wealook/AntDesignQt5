#include "DemoTypography.h"
#include "Card.h"
#include "QLayout"
#include "VWidget.h"
#include "Title.h"
#include "Text.h"

DemoTypography::DemoTypography(QWidget *parent) : DemoContentWidget(parent) {

    {
        auto *card = new wl::Card();
        auto *vWidget = new wl::VWidget();
        vWidget->addWidget(new wl::Title("h1. Ant Design", 1));
        vWidget->addWidget(new wl::Title("h2. Ant Design", 2));
        vWidget->addWidget(new wl::Title("h3. Ant Design", 3));
        vWidget->addWidget(new wl::Title("h4. Ant Design", 4));
        vWidget->addWidget(new wl::Title("h5. Ant Design", 5));
        card->setContentWidget(vWidget);
        layoutLeft_->addWidget(card);
    }
    {
        auto *card = new wl::Card();
        auto *vWidget = new wl::VWidget();
        {
            auto *text = new wl::Text("Ant Design (default)");
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (secondary)");
            text->setAttrType(wl::GeneralAttrColorType::secondary);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (success)");
            text->setAttrType(wl::GeneralAttrColorType::success);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (warning)");
            text->setAttrType(wl::GeneralAttrColorType::warning);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (danger)");
            text->setAttrType(wl::GeneralAttrColorType::danger);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (underline)");
            text->setAttrMark(true);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (code)");
            text->setAttrCode(true);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (keyboard)");
            text->setAttrKeyboard(true);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (underline)");
            text->setAttrUnderline(true);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (destroy)");
            text->setAttrDestroy(true);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }

        {
            auto *text = new wl::Text("Ant Design (strong)");
            text->setAttrStrong(true);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (italic)");
            text->setAttrItalic(true);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }
        {
            auto *text = new wl::Text("Ant Design (link)");
            text->setAttrLink(true);
            text->setContentsMargins(0, 10, 0, 10);
            vWidget->addWidget(text);
        }

        card->setContentWidget(vWidget);
        layoutRight_->addWidget(card);
    }
}
