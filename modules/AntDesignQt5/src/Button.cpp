
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


    Button::Button(QWidget *parent) : QWidget(parent) {
    }


    void Button::setButtonAttr(const ButtonAttr &aButtonAttr) {
        auto themeConfig = ThemeConfig::Instance();
        this->buttonAttr = aButtonAttr;
        auto sizeHeight = wl::getSizeHeight(aButtonAttr.size) + 0;
        auto sizeHeightFull = sizeHeight + 8;
        this->setWindowFlags(Qt::FramelessWindowHint); // 设置窗口标记来取消默认阴影

        this->setStyleQss("padding", "4px");
        this->setStyleQss("padding-bottom", "4px");
        this->setStyleQss("padding-left", "4px");
        this->setStyleQss("padding-right", "4px");
        QFont font;
        font.setPixelSize(sizeHeight);
        this->setFont(font);
        if (label_) {
            label_->setFont(font);
        }
        this->setMinimumHeight(sizeHeightFull);
        this->setFixedHeight(sizeHeightFull);
        std::string mainColor = themeConfig.colorPrimary;
        std::string mainColorHover = themeConfig.colorPrimaryHover;

        Util::fromCssColor(mainColor);
        Util::fromCssColor("rgb(1,1,1 )");
        Util::fromCssColor("rgba(  11 , 13 , 14,123 )");
        if (aButtonAttr.danger) {
            mainColor = themeConfig.colorDanger;
            mainColorHover = themeConfig.colorDangerHover;
        }
        if (aButtonAttr.shape == GeneralAttrShape::circle) {
            this->setFixedWidth(sizeHeightFull);
            this->setStyleQss("border-radius", std::to_string(this->height() / 2) + "px");
        }
        if (aButtonAttr.shape == GeneralAttrShape::round) {
            this->setStyleQss("border-radius", std::to_string(themeConfig.borderRadius) + "px");
        }
        if (aButtonAttr.type == ButtonAttrType::primary) {
            this->setStyleQss("background-color", mainColor);
            this->setStyleQss("color", "#FFFFFF");
            this->setStyleQss("border", "none");

            this->setStyleQss("hover", "background-color", mainColorHover);
            this->setStyleQss("hover", "color", "#FFFFFF");
            this->setStyleQss("hover", "border", "none");
        }

        if (aButtonAttr.type == ButtonAttrType::dashed) {
            this->setStyleQss("background-color", "rgba(255,255,255,0)");
            this->setStyleQss("color", "#000000");

            this->setStyleQss("border-style", "dashed");
            this->setStyleQss("border-width", "1px");
            this->setStyleQss("border-color", themeConfig.colorBorder);


            this->setStyleQss("hover", "color", themeConfig.colorPrimary);
            this->setStyleQss("hover", "border-color", themeConfig.colorPrimary);
        }


        if (aButtonAttr.type == ButtonAttrType::text) {
            this->setStyleQss("background-color", "rgba(255,255,255,0)");
            this->setStyleQss("color", "rgb(0,0,0)");
            this->setStyleQss("border", "none");

            this->setStyleQss("hover", "background-color", themeConfig.colorBgSecondary);
        }
        if (aButtonAttr.type == ButtonAttrType::none) {
            this->setStyleQss("background-color", "rgba(255,255,255,0)");
            this->setStyleQss("color", "#000000");
            this->setStyleQss("border-width", "1px");
            this->setStyleQss("border-style", "solid");
            this->setStyleQss("border-color", themeConfig.colorBorder);

            this->setStyleQss("hover", "color", themeConfig.colorPrimary);
            this->setStyleQss("hover", "border-color", themeConfig.colorPrimary);
        }
        if (aButtonAttr.type == ButtonAttrType::link) {
            this->setStyleQss("border", "none");
            this->setStyleQss("background-color", "rgba(255,255,255,0)");
            this->setStyleQss("color", themeConfig.colorPrimary);
            this->setStyleQss("hover", "color", themeConfig.colorPrimaryHover);
        }
        if (aButtonAttr.disabled) {
            this->setStyleQss("background-color", themeConfig.colorDisabled);
            this->setStyleQss("color", themeConfig.colorDisabledText);
            this->setStyleQss("border-color", themeConfig.colorDisabledBorder);
            this->setStyleQss("border-width", "1px");
            this->setStyleQss("border-style", "solid");
        }
        this->setStyleSheet(this->getJoinStyles("!hover"));
//        this->setStyleSheet(this->getJoinStyles());
        this->setDisabled(aButtonAttr.disabled);
        if (this->buttonAttr.disabled) {
            this->setCursor(Qt::ForbiddenCursor);
        }

        if (this->buttonAttr.icon.has_value()) {
            if (icon_) {
                icon_->setParent(nullptr);
                this->layout()->removeWidget(icon_);
                delete icon_;
            }
            if (iconHover_) {
                iconHover_->setParent(nullptr);
                this->layout()->removeWidget(iconHover_);
                delete iconHover_;
            }
            icon_ = new Icon(QString::fromStdString(std::string(magic_enum::enum_name(this->buttonAttr.icon.value()))),
                             Util::fromCssColor(this->getStyleQss("!hover", "color")));
            icon_->setFixedSize(sizeHeight - 4, sizeHeight - 4);
            iconHover_ = new Icon(QString::fromStdString(std::string(magic_enum::enum_name(this->buttonAttr.icon.value()))),
                                  Util::fromCssColor(this->getStyleQss("hover", "color")));
            iconHover_->setFixedSize(sizeHeight - 4, sizeHeight - 4);
        }
        this->leaveEvent(nullptr);

    }

    const ButtonAttr &Button::getButtonAttr() const {
        return buttonAttr;
    }

    void Button::mouseMoveEvent(QMouseEvent *e) {
        QPalette palette;
        palette.setColor(QPalette::ButtonText, Qt::red); // 文字颜色设置为白色
        this->setPalette(palette);
//        QAbstractButton::mouseMoveEvent(e);
    }

    Button::Button(const QString &text, const ButtonAttr &aButtonAttr, QWidget *parent) : QWidget(parent) {
        this->buttonAttr = aButtonAttr;

        this->setMouseTracking(true);
        this->setMinimumWidth(20);
        this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        label_ = new QLabel(text);
        auto *ly = new QHBoxLayout(this);
        ly->setMargin(1);
        ly->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        if (text.length() == 0) {
            label_->setFixedSize(0, 0);
            ly->setSpacing(0);

        } else {
            ly->setSpacing(4);
        }
        ly->addWidget(label_);
        ly->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        this->setButtonAttr(aButtonAttr);

    }

    bool Button::eventFilter(QObject *watched, QEvent *event) {

        return QObject::eventFilter(watched, event);
    }

    void Button::mousePressEvent(QMouseEvent *event) {
        LOG_INFO("click")
        QWidget::mousePressEvent(event);
    }

    void Button::mouseReleaseEvent(QMouseEvent *event) {
        QWidget::mouseReleaseEvent(event);
    }

    void Button::mouseDoubleClickEvent(QMouseEvent *event) {
        QWidget::mouseDoubleClickEvent(event);
    }

    void Button::enterEvent(QEvent *event) {
        if (this->buttonAttr.icon.has_value()) {
            if (this->layout()->indexOf(icon_) >= 0) {
                icon_->setParent(nullptr);
                this->layout()->takeAt(this->layout()->indexOf(icon_));
            }
            auto *layout = dynamic_cast<QHBoxLayout *>(this->layout());
            if (this->buttonAttr.iconPosition == ButtonAttrIconPosition::prefix) {
                layout->insertWidget(1, iconHover_);
            } else {
                layout->insertWidget(2, iconHover_);
            }
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
            QWidget::enterEvent(event);
        }
    }

    void Button::leaveEvent(QEvent *event) {
        if (this->buttonAttr.icon.has_value()) {
            if (this->layout()->indexOf(iconHover_) >= 0) {
                iconHover_->setParent(nullptr);
                this->layout()->takeAt(this->layout()->indexOf(iconHover_));
            }
            auto *layout = dynamic_cast<QHBoxLayout *>(this->layout());
            if (this->buttonAttr.iconPosition == ButtonAttrIconPosition::prefix) {
                layout->insertWidget(1, icon_);
            } else {
                layout->insertWidget(2, icon_);
            }
        }
//        LOG_INFO("level ")
        this->setStyleSheet(this->getJoinStyles("!hover"));
        auto innerStyles1 = "color:" + this->getStyleQss("!hover", "color") + ";";
        innerStyles1 += "background-color:" + this->getStyleQss("!hover", "background-color") + "; ";
//        innerStyles1 += "border-radius:" + this->getStyleQss("!hover", "border-radius") + ";";

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
            QWidget::enterEvent(event);
        }
    }
}