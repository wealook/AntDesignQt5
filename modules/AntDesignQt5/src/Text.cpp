
#include "Text.h"
#include "QLayout"
#include "QLabel"
#include "ThemeConfig.h"

namespace wl {

    Text::Text(const QString &text, QWidget *parent) : HWidget(parent) {
//        this->setFixed();
        this->setMinimumWidth(10);
        label_ = new QLabel(text);
        label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        this->addWidget(label_);
        // debug
//        this->setStyleQss("border","1px solid blue");
        this->setStyleQss("border", "none");
        this->setStyleSheet(this->getJoinStyles());
    }

    void Text::setAttr(const TextAttr &textAttr) {
        this->attr_ = textAttr;
        auto themeConfig = ThemeConfig::Instance();
        AWidget aWidget;

        aWidget.setStyleQss("border-radius", "none");
        aWidget.setStyleQss("padding", "0px");
        aWidget.setStyleQss("margin", "0px");
        aWidget.setStyleQss("text-align", "left");
//        aWidget.setStyleQss("height", "24px");

        aWidget.setStyleQss("font-size", std::to_string(attr_.fontSize) + "px");
        if (this->attr_.type == GeneralAttrColorType::secondary) {
            aWidget.setStyleQss("color", themeConfig.colorTextSecondary);
        } else if (this->attr_.type == GeneralAttrColorType::success) {
            aWidget.setStyleQss("color", themeConfig.colorSuccessText);
        } else if (this->attr_.type == GeneralAttrColorType::warning) {
            aWidget.setStyleQss("color", themeConfig.colorWarningText);
        } else if (this->attr_.type == GeneralAttrColorType::danger) {
            aWidget.setStyleQss("color", themeConfig.colorErrorText);
        } else {
        }
        if (this->attr_.mark) {
            aWidget.setStyleQss("background-color", themeConfig.colorBgTextMark);
        }
        if (this->attr_.code) {
            aWidget.setStyleQss("background-color", themeConfig.colorBgTextCode);
        }
        if (this->attr_.keyboard) {
            aWidget.setStyleQss("background-color", themeConfig.colorBgTextKeyword);
        }
        if (this->attr_.underline) {
            aWidget.setStyleQss("text-decoration", "underline");
        }
        if (this->attr_.destroy) {
            aWidget.setStyleQss("text-decoration", "line-through");
        }
        if (this->attr_.strong) {
            aWidget.setStyleQss("font-weight", "600");
        }
        if (this->attr_.italic) {
            aWidget.setStyleQss("font-style", "italic");
        }
        if (this->attr_.link) {
        }
        label_->setStyleSheet(aWidget.getJoinStyles());
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
}