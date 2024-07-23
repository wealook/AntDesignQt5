
#include "Text.h"
#include "QLayout"
#include "QLabel"
#include "AWidget.h"
#include "ThemeConfig.h"

namespace wl {

    Text::Text(const QString &text, QWidget *parent) : QWidget(parent) {
        this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        this->setMinimumWidth(10);
        auto *ly = new QHBoxLayout(this);
        ly->setSpacing(0);
        ly->setMargin(0);
        label_ = new QLabel(text);
        label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        ly->addWidget(label_);
    }

    void Text::setAttr(const TextAttr &textAttr) {
        this->attr_ = textAttr;
        auto themeConfig = ThemeConfig::Instance();
        AWidget aWidget;
        aWidget.setStyleQss("height", "24px");
        aWidget.setStyleQss("font-size", "16px");
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
}