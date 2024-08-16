
#include <QStyleOption>
#include "Switch.h"
#include "ThemeConfig.h"
#include "QPainter"
#include "Text.h"
#include "QHBoxLayout"
#include <QPropertyAnimation>
#include "QVariant"

namespace wl {

    Switch::Switch(SwitchAttr attr, QWidget *parent) : HWidget(parent) {
        this->setFixed();
        connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
        this->updateAttr(attr);
        this->enterEventCB = [this](QEvent *event) {
            center->setStyleQssFource("background-color", "white");
            center->setStyleSheet(center->getJoinStyles());
        };
        this->leaveEventCB = [this](QEvent *event) {
            LOG_INFO("leaveEventCB")
            center->setStyleQssFource("background-color", "white");
            center->setStyleSheet(center->getJoinStyles());
        };
//        animation->setStartValue(QVariant(Qt::blue)); // 按钮按下时的颜色
//        animation->setEndValue(Qt::red);   // 按钮释放时的颜色
//        connect(this, SIGNAL(clicked()), animation, &QPropertyAnimation::start);

    }

    void Switch::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        {
//            https://blog.csdn.net/dee53994040/article/details/102178938
            // 修复使用了 Q_OBJECT 后stylesheet无效的问题
            QStyleOption opt;
            opt.init(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
        }
    }

    void Switch::onClicked() {
        LOG_INFO("onClicked")
        if (!this->attr.disabled) {
            attr.checked = !attr.checked;
            this->updateAttr(attr);
            this->enterEvent(nullptr);
        }
        emit changed(attr.checked);
    }

    void Switch::updateAttr(SwitchAttr attrPa) {
        this->attr = attrPa;
        auto themeConfig = ThemeConfig::Instance();
        if (this->attr.size == GeneralAttrSize::small) {
            this->setFixedHeight(16);
            this->setMinimumWidth(30);
        } else {
            this->setFixedHeight(22);
            this->setMinimumWidth(44);
        }
        auto h = this->height();
        auto parentRadius = std::to_string(h / 2) + "px";
        this->setStyleQss("border-radius", parentRadius);
        if (!center) {
            center = new HWidget();
//            auto *animation = new QPropertyAnimation(center, "pos");
//            animation->setDuration(1000);
        }
        if (!left && !right) {
            left = new HWidget();
            if (this->attr.checkedChildren) {
                left->addWidget(this->attr.checkedChildren);
            }
            left->setStyleQss("padding-left", parentRadius);
            left->setStyleSheet(left->getJoinStyles());
            right = new HWidget();
            if (this->attr.unCheckedChildren) {
                right->addWidget(this->attr.unCheckedChildren);
            }
            right->setStyleQss("padding-right", parentRadius);
            right->setStyleSheet(right->getJoinStyles());

            this->addWidget(left);
            this->addWidget(center);
            this->addWidget(right);
        }

        if (this->attr.checked) {
//            this->setStyleQssFource("padding-left", parentRadius);
//            this->setStyleQssFource("padding-right", parentRadius);
            center->setStyleQssFource("margin-left", "0px");
            center->setStyleQssFource("margin-right", "2px");
            if (this->attr.disabled) {
                this->setStyleQss("background-color", themeConfig.colorPrimaryHover);
            } else {
                this->setStyleQss("background-color", themeConfig.colorPrimary);
                this->setStyleQss("hover", "background-color", themeConfig.colorPrimaryHover);
            }
        } else {
//            this->setStyleQssFource("padding-left", parentRadius);
//            this->setStyleQssFource("padding-right", parentRadius);
            center->setStyleQssFource("margin-left", "2px");
            center->setStyleQssFource("margin-right", "0px");
            center->setStyleQss("background-color", "rgba(0,0,0,0)");
            if (this->attr.disabled) {
                this->setStyleQss("background-color", themeConfig.colorDisabledBorder);
            } else {
                this->setStyleQss("background-color", themeConfig.colorDisabledDepth);
                this->setStyleQss("hover", "background-color", themeConfig.colorTextDisabled);
            }
        }
        this->setStyleQss("color", "white");
        this->setStyleSheet(this->getJoinStyles());
        center->setFixedSize(h - 2, h - 4);
        center->setStyleQss("border-radius", std::to_string(center->height() / 2) + "px");
        center->setStyleQss("background-color", "white");
        center->setStyleSheet(center->getJoinStyles());


        if (this->attr.checked) {
            left->setVisible(true);
            right->setVisible(false);
        } else {
            left->setVisible(false);
            right->setVisible(true);
        }
        this->setStyleSheet(this->getJoinStyles());
    }
}
