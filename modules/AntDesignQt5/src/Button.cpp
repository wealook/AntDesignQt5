
#include "Button.h"
#include "ASizeHelper.h"
#include "logger.h"
#include "ThemeConfig.h"
#include "Helper.h"
#include "QLayout"
#include "qevent.h"
#include "../../../3rdparty/magic_enum/magic_enum.hpp"
#include "Util.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace wl {


    void Button::updateAttr() {
        this->clearStyleQss();
        auto themeConfig = ThemeConfig::Instance();
        auto sizeHeight = wl::getSizeHeight(this->attrSize) + 0;
        auto sizeHeightFull = sizeHeight + 8;
        this->setWindowFlags(Qt::FramelessWindowHint); // 设置窗口标记来取消默认阴影

        if (this->attrBlock) {
            this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        } else {
            this->setFixed();
        }
        this->setContentsMargins(4, 4, 4, 4);
        QFont font;
        font.setPixelSize(sizeHeight);
        this->setFont(font);
        if (label_) {
            label_->setFont(font);
        }
        this->label_->setVisible(!this->label_->text().isEmpty());
        this->setMinimumHeight(sizeHeightFull);
        this->setFixedHeight(sizeHeightFull);
        std::string mainColor = themeConfig.colorPrimary;
        std::string mainColorHover = themeConfig.colorPrimaryHover;
        if (this->attrDanger) {
            mainColor = themeConfig.colorDanger;
            mainColorHover = themeConfig.colorDangerHover;
        }

        if (this->attrShape == GeneralAttrShape::circle) {
            this->setFixedWidth(sizeHeightFull);
            this->setStyleQss("border-radius", std::to_string(this->height() / 2) + "px");
        } else if (this->attrShape == GeneralAttrShape::round) {
            this->setStyleQss("border-radius", std::to_string(themeConfig.borderRadius) + "px");
        } else {
            this->setStyleQss("border-radius", "none");
        }

        if (this->attrType == ButtonAttrType::primary) {
            this->setStyleQss("background-color", mainColor);
            this->setStyleQss("color", "#FFFFFF");
            this->setStyleQss("border", "none");

            this->setStyleQss("hover", "background-color", mainColorHover);
            this->setStyleQss("hover", "color", "#FFFFFF");
            this->setStyleQss("hover", "border", "none");
        } else if (this->attrType == ButtonAttrType::dashed) {
            this->setStyleQss("background-color", "rgba(255,255,255,0)");
            this->setStyleQss("color", "#000000");

            this->setStyleQss("border-style", "dashed");
            this->setStyleQss("border-width", "1px");
            this->setStyleQss("border-color", themeConfig.colorBorder);


            this->setStyleQss("hover", "color", themeConfig.colorPrimary);
            this->setStyleQss("hover", "border-color", themeConfig.colorPrimary);
        } else if (this->attrType == ButtonAttrType::text) {
            this->setStyleQss("background-color", "rgba(255,255,255,0)");
            this->setStyleQss("color", "rgb(0,0,0)");
            this->setStyleQss("border", "none");

            this->setStyleQss("hover", "background-color", themeConfig.colorBgSecondary);
        } else if (this->attrType == ButtonAttrType::none) {
            this->setStyleQss("background-color", "rgba(255,255,255,0)");
            this->setStyleQss("color", "#000000");
            this->setStyleQss("border-width", "1px");
            this->setStyleQss("border-style", "solid");
            this->setStyleQss("border-color", themeConfig.colorBorder);
            this->setStyleQss("hover", "background-color", "rgba(255,255,255,0)");
            this->setStyleQss("hover", "color", themeConfig.colorPrimary);
            this->setStyleQss("hover", "border-color", themeConfig.colorPrimary);
        } else if (this->attrType == ButtonAttrType::link) {
            this->setStyleQss("border", "none");
            this->setStyleQss("background-color", "rgba(255,255,255,0)");
            this->setStyleQss("color", themeConfig.colorPrimary);
            this->setStyleQss("hover", "color", themeConfig.colorPrimaryHover);
        }
        if (this->attrDisabled) {
            this->setStyleQss("background-color", themeConfig.colorDisabled);
            this->setStyleQss("color", themeConfig.colorDisabledText);
            this->setStyleQss("border-color", themeConfig.colorDisabledBorder);
            this->setStyleQss("border-width", "1px");
            this->setStyleQss("border-style", "solid");
        }
        this->setStyleSheet(this->getJoinStyles("!hover"));
//        this->setStyleSheet(this->getJoinStyles());
        this->setDisabled(this->attrDisabled);
        if (this->attrDisabled) {
            this->setCursor(Qt::ForbiddenCursor);
        }


        if (this->attrIconPosition == ButtonAttrIconPosition::postfix) {
            this->removeWidget(this->label_);
            this->removeWidget(this->iconWidget_);
            this->insertWidget(1, this->label_);
            this->insertWidget(2, this->iconWidget_);
        } else {
            this->removeWidget(this->label_);
            this->removeWidget(this->iconWidget_);
            this->insertWidget(1, this->iconWidget_);
            this->insertWidget(2, this->label_);
        }
        if (this->attrIcon.has_value()) {
            this->iconWidget_->setFixedSize(sizeHeight - 4, sizeHeight - 4);
            this->iconWidget_->setVisible(true);
            this->icon_->changeColor(Util::fromCssColor(this->getStyleQss("!hover", "color")));
        } else {
            this->iconWidget_->setFixedSize(0, 0);
            this->iconWidget_->setVisible(false);
        }
        label_->setAlignment(Qt::AlignCenter);
        this->leaveEvent(nullptr);
    }


    void Button::mouseMoveEvent(QMouseEvent *e) {
        QPalette palette;
        palette.setColor(QPalette::ButtonText, Qt::red); // 文字颜色设置为白色
        this->setPalette(palette);
//        QAbstractButton::mouseMoveEvent(e);
    }

    Button::Button(const QString &text, QWidget *parent) : HWidget(parent) {
        this->globalHover = false;
        this->setFixed();
        this->setMouseTracking(true);
        this->setMinimumWidth(20);
//        this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        iconWidget_ = new HWidget(this);
        label_ = new QLabel(text);

        auto *ly = this->layout();
        ly->setMargin(1);
        ly->addItem(new QSpacerItem(1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

        if (text.length() == 0) {
            label_->setFixedSize(0, 0);
            ly->setSpacing(0);
        } else {
            ly->setSpacing(4);
        }

        ly->addWidget(iconWidget_);
        ly->addWidget(label_);
        ly->addItem(new QSpacerItem(1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        this->updateAttr();
    }


    void Button::enterEvent(QEvent *event) {
        if (this->attrIcon.has_value()) {
            this->icon_->changeColor(Util::fromCssColor(this->getStyleQss("hover", "color")));
        }
        this->setStyleSheet(this->getJoinStyles("hover", false));

        auto innerStyles1 = "color:" + this->getStyleQss("hover", "color") + ";";
        innerStyles1 += "background-color:" + this->getStyleQss("hover", "background-color") + ";";
//        innerStyles1 += "border-radius:" + this->getStyleQss("hover", "border-radius") + ";";
        if (this->layout() != nullptr) {
            QLayoutItem *child;
            auto count = this->layout()->count();
            for (int index = 0; index < count; index++) {
                child = this->layout()->itemAt(index);
                if (child && child->widget()) {
                    child->widget()->setStyleSheet(QString::fromStdString(innerStyles1 + "border:none; padding:0px;"));
                }
            }
        }
        if (event != nullptr) {
            wl::HWidget::enterEvent(event);
        }
    }

    void Button::leaveEvent(QEvent *event) {
        if (this->attrIcon.has_value()) {
            this->icon_->changeColor(Util::fromCssColor(this->getStyleQss("!hover", "color")));
        }
        this->setStyleSheet(this->getJoinStyles("!hover"));
        auto innerStyles1 = "color:" + this->getStyleQss("!hover", "color") + ";";
        innerStyles1 += "background-color:" + this->getStyleQss("!hover", "background-color") + "; ";

        if (this->layout() != nullptr) {
            QLayoutItem *child;
            auto count = this->layout()->count();
            for (int index = 0; index < count; index++) {
                child = this->layout()->itemAt(index);
                if (child && child->widget()) {
                    child->widget()->setStyleSheet(QString::fromStdString(innerStyles1 + "border:none;padding:0px; "));
                }
            }
        }
        if (event != nullptr) {
            wl::HWidget::enterEvent(event);
        }
    }

    void Button::setAttrType(ButtonAttrType buttonAttrType) {
        Button::attrType = buttonAttrType;
    }

    void Button::setAttrLoading(bool loading) {
        Button::attrLoading = loading;
    }

    void Button::setAttrBlock(bool blck) {
        Button::attrBlock = blck;
    }

    void Button::setAttrDisabled(bool disabled) {
        Button::attrDisabled = disabled;
    }

    void Button::setAttrDanger(bool danger) {
        Button::attrDanger = danger;
    }

    void Button::setAttrSize(GeneralAttrSize size) {
        Button::attrSize = size;
    }

    void Button::setAttrShape(GeneralAttrShape generalAttrShape) {
        Button::attrShape = generalAttrShape;
    }

    void Button::setAttrIcon(const std::optional<IconSvg> &icon) {

        if (this->attrIcon.has_value() && this->attrIcon.value() == icon) {
            return;
        }
        if (icon_ != nullptr) {
            this->iconWidget_->removeWidget(icon_, true);
        }
        this->attrIcon = icon;
        icon_ = new Icon(QString::fromStdString(std::string(magic_enum::enum_name(this->attrIcon.value()))),
                         Util::fromCssColor(this->getStyleQss("!hover", "color")), this);
        iconWidget_->addWidget(icon_);
    }

    void Button::setAttrIconPosition(ButtonAttrIconPosition position) {
        Button::attrIconPosition = position;
    }

    void Button::paintEvent(QPaintEvent *event) {
        HWidget::paintEvent(event);
    }


}