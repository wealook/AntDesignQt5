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
        layout->addWidget(new wl::Button(
                "Primary Button",
                wl::ButtonAttr(wl::ButtonAttrType::primary, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::round),
                this
        ));
        layout->addWidget(new wl::Button(
                "Default Button",
                wl::ButtonAttr(wl::ButtonAttrType::none, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::round),
                this
        ));
        layout->addWidget(new wl::Button(
                "Dashed Button",
                wl::ButtonAttr(wl::ButtonAttrType::dashed, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::round),
                this
        ));
        layout->addWidget(new wl::Button(
                "Text Button",
                wl::ButtonAttr(wl::ButtonAttrType::text, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::round),
                this
        ));
        layout->addWidget(new wl::Button(
                "Link Button",
                wl::ButtonAttr(wl::ButtonAttrType::link, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::round),
                this
        ));
        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));

        card->setContentWidget(widget);
        this->layoutLeft_->addWidget(card);
    }
    {
        auto *card = new wl::Card();
        auto *widget = new QWidget();
        widget->setStyleSheet("border:none;");
        auto *layout = new QHBoxLayout(widget);
        layout->addWidget(new wl::Button(
                "Primary Button",
                wl::ButtonAttr(wl::ButtonAttrType::primary, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::none),
                this
        ));
        layout->addWidget(new wl::Button(
                "Default Button",
                wl::ButtonAttr(wl::ButtonAttrType::none, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::none),
                this
        ));
        layout->addWidget(new wl::Button(
                "Dashed Button",
                wl::ButtonAttr(wl::ButtonAttrType::dashed, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::none),
                this
        ));
        layout->addWidget(new wl::Button(
                "Text Button",
                wl::ButtonAttr(wl::ButtonAttrType::text, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::none),
                this
        ));
        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));

        card->setContentWidget(widget);
        this->layoutLeft_->addWidget(card);
    }
    {
        auto *card = new wl::Card();
        auto *widget = new QWidget();
        widget->setStyleSheet("border:none;");
        auto *layout = new QHBoxLayout(widget);
        auto *btn = new wl::Button(
                "",
                wl::ButtonAttr(wl::ButtonAttrType::primary, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::circle, wl::IconSvg::SearchOutlined),
                this
        );
//        auto* btn = new QPushButton("Test");
        auto icon = wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::SearchOutlined))), Qt::white);
        layout->addWidget(btn);
        layout->addWidget(new wl::Button(
                "A",
                wl::ButtonAttr(wl::ButtonAttrType::primary, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::circle),
                this
        ));
        layout->addWidget(new wl::Button(
                "Search",
                wl::ButtonAttr(wl::ButtonAttrType::primary, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::none, wl::IconSvg::SearchOutlined),
                this
        ));
        layout->addWidget(new wl::Button(
                "",
                wl::ButtonAttr(wl::ButtonAttrType::none, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::circle, wl::IconSvg::SearchOutlined),
                this
        ));
        layout->addWidget(new wl::Button(
                "Search",
                wl::ButtonAttr(wl::ButtonAttrType::none, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::round, wl::IconSvg::SearchOutlined),
                this
        ));
        layout->addWidget(new wl::Button(
                "",
                wl::ButtonAttr(wl::ButtonAttrType::dashed, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::circle, wl::IconSvg::SearchOutlined),
                this
        ));
        layout->addWidget(new wl::Button(
                "Search",
                wl::ButtonAttr(wl::ButtonAttrType::dashed, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::round, wl::IconSvg::SearchOutlined),
                this
        ));

        layout->addWidget(new wl::Button(
                "",
                wl::ButtonAttr(wl::ButtonAttrType::dashed, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::round, wl::IconSvg::SearchOutlined),
                this
        ));
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
        auto attr = wl::ButtonAttr(wl::ButtonAttrType::primary, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::circle, wl::IconSvg::SearchOutlined);
        attr.iconPosition = wl::ButtonAttrIconPosition::postfix;
        auto *btn = new wl::Button(
                "", attr,
                this
        );
//        auto* btn = new QPushButton("Test");
        auto icon = wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(wl::IconSvg::SearchOutlined))), Qt::white);
        layout->addWidget(btn);
        layout->addWidget(new wl::Button(
                "A",
                wl::ButtonAttr(wl::ButtonAttrType::primary, wl::GeneralAttrSize::middle, wl::GeneralAttrShape::circle),
                this
        ));
        attr.shape = wl::GeneralAttrShape::round;
        layout->addWidget(new wl::Button(
                "Search",
                attr,
                this
        ));
        attr.disabled = true;
        layout->addWidget(new wl::Button(
                "",
                attr,
                this
        ));
        layout->addWidget(new wl::Button(
                "Search",
                attr,
                this
        ));
        attr.danger = true;
        attr.disabled = false;

        layout->addWidget(new wl::Button(
                "",
                attr,
                this
        ));
        layout->addWidget(new wl::Button(
                "Search",
                attr,
                this
        ));

        layout->addWidget(new wl::Button(
                "",
                attr,
                this
        ));
        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        card->setContentWidget(widget);
        this->layoutLeft_->addWidget(card);
    }
}
