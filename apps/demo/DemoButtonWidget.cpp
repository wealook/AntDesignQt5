#include "DemoButtonWidget.h"
#include "Card.h"
#include "Button.h"
#include "Icon.h"
#include "magic_enum.hpp"

DemoButtonWidget::DemoButtonWidget(QWidget *parent) : DemoContentWidget(parent) {
    {
        auto *card = new wl::Card();
        auto *widget = new QWidget();
        widget->setStyleSheet("border:none;");
        auto *layout = new QHBoxLayout(widget);
        {
            auto *btn = new wl::Button("Primary Button", this);
            btn->setAttrType(wl::ButtonAttrType::primary);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::round);
            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Default Button", this);
            btn->setAttrType(wl::ButtonAttrType::none);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::round);
            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Dashed Button", this);
            btn->setAttrType(wl::ButtonAttrType::dashed);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::round);
            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Text Button", this);
            btn->setAttrType(wl::ButtonAttrType::text);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::round);
            btn->updateAttr();

            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Link Button", this);
            btn->setAttrType(wl::ButtonAttrType::link);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::round);
            btn->updateAttr();
            layout->addWidget(btn);
        }

        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));

        card->setContentWidget(widget);
        this->layoutLeft_->addWidget(card);
    }
    {
        auto *card = new wl::Card();
        auto *widget = new QWidget();
        widget->setStyleSheet("border:none;");
        auto *layout = new QHBoxLayout(widget);
        {
            auto *btn = new wl::Button("Primary Button", this);
            btn->setAttrType(wl::ButtonAttrType::primary);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::none);
            btn->setAttrDanger(true);
            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Default Button", this);
            btn->setAttrType(wl::ButtonAttrType::none);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::none);
            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Dashed Button", this);
            btn->setAttrType(wl::ButtonAttrType::dashed);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::none);
            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Text Button", this);
            btn->setAttrType(wl::ButtonAttrType::text);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::none);
            btn->updateAttr();
            layout->addWidget(btn);
        }

        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));

        card->setContentWidget(widget);
        this->layoutLeft_->addWidget(card);
    }
    {
        auto *card = new wl::Card();
        auto *widget = new QWidget();
        widget->setStyleSheet("border:none;");
        auto *layout = new QHBoxLayout(widget);
        {
            auto *btn = new wl::Button("", this);
            btn->setAttrType(wl::ButtonAttrType::primary);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::circle);
            btn->setAttrIcon(wl::IconSvg::SearchOutlined);
            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("A", this);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::circle);
            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Search", this);
            btn->setAttrType(wl::ButtonAttrType::primary);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::none);
            btn->setAttrIcon(wl::IconSvg::SearchOutlined);

            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("", this);
            btn->setAttrType(wl::ButtonAttrType::none);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::circle);
            btn->setAttrIcon(wl::IconSvg::SearchOutlined);
            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Search", this);
            btn->setAttrType(wl::ButtonAttrType::none);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::round);
            btn->setAttrIcon(wl::IconSvg::SearchOutlined);

            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("", this);
            btn->setAttrType(wl::ButtonAttrType::dashed);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::circle);
            btn->setAttrIcon(wl::IconSvg::SearchOutlined);

            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Search", this);
            btn->setAttrType(wl::ButtonAttrType::dashed);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::round);
            btn->setAttrIcon(wl::IconSvg::SearchOutlined);

            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("", this);
            btn->setAttrType(wl::ButtonAttrType::dashed);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::round);
            btn->setAttrIcon(wl::IconSvg::SearchOutlined);

            btn->updateAttr();
            layout->addWidget(btn);
        }

        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        card->setContentWidget(widget);
        this->layoutRight_->addWidget(card);
    }
    {
        // 图标后置
        auto *card = new wl::Card();
        auto *widget = new QWidget();
        widget->setStyleSheet("border:none;");
        auto *layout = new QHBoxLayout(widget);
        {
            auto *btn = new wl::Button("", this);
            btn->setAttrType(wl::ButtonAttrType::dashed);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::circle);
            btn->setAttrIcon(wl::IconSvg::SearchOutlined);
            btn->setAttrIconPosition(wl::ButtonAttrIconPosition::postfix);
            btn->updateAttr();

            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("A", this);
            btn->setAttrType(wl::ButtonAttrType::primary);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::circle);
            btn->updateAttr();

            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button(u8"中", this);
            btn->setAttrType(wl::ButtonAttrType::primary);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::circle);
            btn->updateAttr();

            layout->addWidget(btn);
        }

        {
            auto *btn = new wl::Button("Search", this);
            btn->setAttrType(wl::ButtonAttrType::primary);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::round);
            btn->setAttrIcon(wl::IconSvg::SearchOutlined);
            btn->setAttrIconPosition(wl::ButtonAttrIconPosition::postfix);
            btn->updateAttr();
            layout->addWidget(btn);
        }
        {
            auto *btn = new wl::Button("Search", this);
            btn->setAttrType(wl::ButtonAttrType::dashed);
            btn->setAttrSize(wl::GeneralAttrSize::middle);
            btn->setAttrShape(wl::GeneralAttrShape::round);
            btn->setAttrIcon(wl::IconSvg::SearchOutlined);
            btn->setAttrIconPosition(wl::ButtonAttrIconPosition::postfix);
            btn->updateAttr();
            layout->addWidget(btn);
        }

        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        card->setContentWidget(widget);
        this->layoutLeft_->addWidget(card);
    }
}
