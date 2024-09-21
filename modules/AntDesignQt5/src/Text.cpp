
#include "Text.h"
#include "QLayout"
#include "QLabel"
#include "ThemeConfig.h"

namespace wl {

    Text::Text(const QString &text, QWidget *parent) : HWidget(parent) {
        this->setMinimumWidth(10);
        label_ = new QLabel(text);
        label_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        this->layout()->setAlignment(Qt::AlignLeft);
        this->addWidget(label_);
        auto theme = ThemeConfig::Instance();
        this->setStyleQss("font-family", theme.fontFamily);
//        this->setStyleQss("border", "1px solid blue");
        this->setStyleSheet(this->getJoinStyles());
        this->updateAttr();
    }


    void Text::mousePressEvent(QMouseEvent *event) {
        wl::HWidget::mousePressEvent(event);
        emit clicked();
    }

    void Text::paintEvent(QPaintEvent *event) {
        HWidget::paintEvent(event);
        this->updateAttr();
    }

    void Text::setText(const QString &text) {
        this->label_->setText(text);
    }

    QString Text::getText() {
        return this->label_->text();
    }

    void Text::updateAttr() {
        auto themeConfig = ThemeConfig::Instance();

        this->setStyleQss("border-radius", "none");
        this->setStyleQss("padding", "0px");
        this->setStyleQss("margin", "0px");

//        this->setStyleQss("text-align", "center");
//         this->setStyleQss("height", "24px");

        this->setStyleQss("font-size", std::to_string(attrFontSize) + "px");
        this->setStyleQss("line-height", std::to_string(attrFontSize + 8) + "px");
        if (this->attrType == GeneralAttrColorType::secondary) {
            this->setStyleQss("color", themeConfig.colorTextSecondary);
        } else if (this->attrType == GeneralAttrColorType::success) {
            this->setStyleQss("color", themeConfig.colorSuccessText);
        } else if (this->attrType == GeneralAttrColorType::warning) {
            this->setStyleQss("color", themeConfig.colorWarningText);
        } else if (this->attrType == GeneralAttrColorType::danger) {
            this->setStyleQss("color", themeConfig.colorErrorText);
        } else {
        }
        if (this->attrMark) {
            this->setStyleQss("background-color", themeConfig.colorBgTextMark);
        }
        if (this->attrCode) {
            this->setStyleQss("background-color", themeConfig.colorBgTextCode);
        }
        if (this->attrKeyboard) {
            this->setStyleQss("background-color", themeConfig.colorBgTextKeyword);
        }
        if (this->attrUnderline) {
            this->setStyleQss("text-decoration", "underline");
        }
        if (this->attrDestroy) {
            this->setStyleQss("text-decoration", "line-through");
        }
        if (this->attrStrong) {
            this->setStyleQss("font-weight", "600");
        }
        if (this->attrItalic) {
            this->setStyleQss("font-style", "italic");
        }
        if (this->attrLink) {
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

    void Text::setAttrMark(bool mark) {
        Text::attrMark = mark;
    }

    void Text::setAttrCode(bool code) {
        Text::attrCode = code;
    }

    void Text::setAttrKeyboard(bool keyboard) {
        Text::attrKeyboard = keyboard;
    }

    void Text::setAttrUnderline(bool underline) {
        Text::attrUnderline = underline;
    }

    void Text::setAttrDestroy(bool destroy) {
        Text::attrDestroy = destroy;
    }

    void Text::setAttrStrong(bool strong) {
        Text::attrStrong = strong;
    }

    void Text::setAttrItalic(bool italic) {
        Text::attrItalic = italic;
    }

    void Text::setAttrLink(bool link) {
        Text::attrLink = link;
    }

    void Text::setAttrFontSize(int fontSize) {
        Text::attrFontSize = fontSize;
    }

    void Text::setAttrType(GeneralAttrColorType colorType) {
        Text::attrType = colorType;
    }
}