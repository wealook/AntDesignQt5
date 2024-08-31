
#include "Tag.h"

#include <utility>
#include "Icon.h"

#include "ThemeConfig.h"
#include "Util.h"

namespace wl {

    Tag::Tag(QString text, QWidget *parent) : HWidget(parent), attrText(std::move(text)) {
        this->setFixed();
        icon_ = new HWidget(this);
        iconClose_ = new HWidget(this);
        connect(iconClose_, &HWidget::clicked, this, [this]() {
            if (this->onClose && !onClose()) {
                return;
            }
            emit closed();
        });
        text_ = new Text(attrText, this);
        this->addWidget(icon_);
        this->addWidget(text_);
        this->addWidget(iconClose_);
        this->updateAttr();
    }


    void Tag::setOnClose(const std::function<bool()> &close) {
        this->onClose = close;
    }

    void Tag::setAttrCloseIcon(QWidget *icon) {
        if (icon != this->attrCloseIcon || (this->attrCloseIcon != nullptr)) {
            if (attrCloseIcon != nullptr) {
                attrCloseIcon->setParent(nullptr);
            }
            this->iconClose_->removeWidget(this->attrCloseIcon);
        }

        this->attrCloseIcon = icon;
        if (this->attrCloseIcon != nullptr) {
            iconClose_->addWidget(this->attrCloseIcon);
        }
        this->updateAttr();
    }

    void Tag::setAttrIcon(QWidget *icon) {
        if (icon != this->attrIcon || (this->attrIcon != nullptr)) {
            if (attrIcon != nullptr) {
                attrIcon->setParent(nullptr);
            }
            this->icon_->removeWidget(this->attrIcon);
        }
        this->attrIcon = icon;
        if (this->attrIcon != nullptr) {
            icon_->addWidget(this->attrIcon);
        }

        this->updateAttr();
    }

    void Tag::setAttrBordered(bool attrBordered) {
        Tag::attrBordered = attrBordered;

        this->updateAttr();
    }

    void Tag::setAttrColor(GeneralAttrColorType attrColor) {
        Tag::attrColor = attrColor;
        this->updateAttr();
    }

    void Tag::setAttrText(const QString &attrText) {
        Tag::attrText = attrText;
        this->updateAttr();
    }

    void Tag::updateAttr() {
        auto theme = ThemeConfig::Instance();
        this->setMinimumHeight(20);
        auto colorText = std::string("#000000");
        auto color = theme.colorBorder;
        auto colorBg = theme.colorBorderBg;
        if (this->attrColor == GeneralAttrColorType::error) {
            color = theme.colorErrorText;
            colorBg = theme.colorErrorBg;
            colorText = color;
        } else if (this->attrColor == GeneralAttrColorType::success) {
            color = theme.colorSuccessText;
            colorText = color;
            colorBg = theme.colorSuccessBg;
        } else if (this->attrColor == GeneralAttrColorType::processing) {
            color = theme.colorInfoText;
            colorText = color;
            colorBg = theme.colorInfoBg;
        } else if (this->attrColor == GeneralAttrColorType::warning) {
            color = theme.colorWarningText;
            colorText = color;
            colorBg = theme.colorWarningBg;
        } else {
        }
        this->setStyleQssFource("background-color", colorBg);
        this->setStyleQssFource("border", "1px solid " + color);
        this->setStyleQssFource("border-radius", std::to_string(theme.borderRadiusSM) + "px");
        this->setStyleSheet(this->getJoinStyles());
        this->setContentsMargins(7, 1, 7, 1);
        mainColor_ = color;

        icon_->setStyleQss("border", "none");
        icon_->setFixedSize(12, 12);
        icon_->setStyleSheet(icon_->getJoinStyles());

        iconClose_->setStyleQss("border", "none");
        iconClose_->setStyleSheet(iconClose_->getJoinStyles());
//        connect(icon, &Icon::clicked, this, [&]() {
//            LOG_INFO("close");
//        });

        iconClose_->setFixed();
        iconClose_->setFixedSize(10 + 3, 10);
        iconClose_->setContentsMargins(3, 0, 0, 0);
        text_->setContentsMargins(7, 0, 0, 0);
        text_->setStyleQssFource("color", colorText);
        text_->setStyleSheet(text_->getJoinStyles());
        this->icon_->setVisible(this->attrIcon != nullptr);
        this->iconClose_->setVisible(this->attrCloseIcon != nullptr);
    }

    GeneralAttrColorType Tag::getAttrColor() const {
        return attrColor;
    }

    QColor Tag::getPrimaryColor() {
        return Util::fromCssColor(mainColor_);
    }
}