
#include "Text.h"
#include "QLayout"
#include "QLabel"
#include "ThemeConfig.h"

namespace wl {

    Text::Text(const QString &text, QWidget *parent) : HWidget(parent) {
        this->setMinimumWidth(10);
        label_ = new QLabel(text);
        label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        this->addWidget(label_);
        auto theme = ThemeConfig::Instance();
        this->setStyleQss("font-family", theme.fontFamily);
//        this->setStyleQss("border","1px solid blue");
        this->setStyleSheet(this->getJoinStyles());
        this->updateAttr();
    }

    void Text::setAttr(const TextAttr &textAttr) {
        this->attr_ = textAttr;
        auto themeConfig = ThemeConfig::Instance();

        this->setStyleQss("border-radius", "none");
        this->setStyleQss("padding", "0px");
        this->setStyleQss("margin", "0px");

//        this->setStyleQss("text-align", "center");
//         this->setStyleQss("height", "24px");

        this->setStyleQss("font-size", std::to_string(attr_.fontSize) + "px");
        if (this->attr_.type == GeneralAttrColorType::secondary) {
            this->setStyleQss("color", themeConfig.colorTextSecondary);
        } else if (this->attr_.type == GeneralAttrColorType::success) {
            this->setStyleQss("color", themeConfig.colorSuccessText);
        } else if (this->attr_.type == GeneralAttrColorType::warning) {
            this->setStyleQss("color", themeConfig.colorWarningText);
        } else if (this->attr_.type == GeneralAttrColorType::danger) {
            this->setStyleQss("color", themeConfig.colorErrorText);
        } else {
        }
        if (this->attr_.mark) {
            this->setStyleQss("background-color", themeConfig.colorBgTextMark);
        }
        if (this->attr_.code) {
            this->setStyleQss("background-color", themeConfig.colorBgTextCode);
        }
        if (this->attr_.keyboard) {
            this->setStyleQss("background-color", themeConfig.colorBgTextKeyword);
        }
        if (this->attr_.underline) {
            this->setStyleQss("text-decoration", "underline");
        }
        if (this->attr_.destroy) {
            this->setStyleQss("text-decoration", "line-through");
        }
        if (this->attr_.strong) {
            this->setStyleQss("font-weight", "600");
        }
        if (this->attr_.italic) {
            this->setStyleQss("font-style", "italic");
        }
        if (this->attr_.link) {
        }
        label_->setStyleSheet(this->getJoinStyles());
        if (this->existStyleQss("!hover", "text-align")) {
            if (this->getStyleQss("!hover", "text-align") == "left") {
                label_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            } else if (this->getStyleQss("!hover", "text-align") == "center") {
                label_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            } else if (this->getStyleQss("!hover", "text-align") == "right") {
                label_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            }
        }
    }

    Text::Text(const QString &text, const TextAttr &textAttr, QWidget *parent) : Text(text, parent) {
        this->setAttr(textAttr);
    }

    void Text::mousePressEvent(QMouseEvent *event) {
        wl::HWidget::mousePressEvent(event);
        emit clicked();
    }

    void Text::paintEvent(QPaintEvent *event) {
        HWidget::paintEvent(event);
        this->setAttr(this->attr_);
    }

    void Text::setText(const QString &text) {
        this->label_->setText(text);
    }

    QString Text::getText() {
        return this->label_->text();
    }

    void Text::updateAttr() {
        this->setAttr(this->attr_);;
    }
}