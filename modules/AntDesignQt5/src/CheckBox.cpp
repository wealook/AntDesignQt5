#include "CheckBox.h"
#include "HWidget.h"
#include "QLayout"
#include "ThemeConfig.h"
#include "QPainter"
#include "Util.h"
#include "QMouseEvent"
#include "QLabel"
#include "QStyleOption"
#include "Text.h"

namespace wl {


    RectCheck::RectCheck(QWidget *parent) : QWidget(parent) {
        auto themeConfig = ThemeConfig::Instance();
        this->setStyleQss("border-radius", std::to_string(themeConfig.borderRadiusSM) + "px");
//            this->setStyleQss("hover", "background-color", themeConfig.colorPrimary);
        this->setStyleQss("border", "1px  solid " + themeConfig.colorDisabledBorder);
        this->setStyleQss("hover", "border", "1px  solid " + themeConfig.colorPrimary);
        this->setStyleSheet(this->getJoinStyles());
        this->setFixedSize(16, 16);
    }

    void RectCheck::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        {
//            https://blog.csdn.net/dee53994040/article/details/102178938
            // 修复使用了 Q_OBJECT 后stylesheet无效的问题
            QStyleOption opt;
            opt.init(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

        }


        QWidget::paintEvent(event);
        auto themeConfig = ThemeConfig::Instance();
        if (state == 0) {
            if (this->isEnabled()) {
                this->setStyleQss("background-color", "none");
                this->setStyleQss("hover", "background-color", "none");
                this->setStyleQss("border", "1px  solid " + themeConfig.colorDisabledBorder);
                this->setStyleQss("hover", "border", "1px  solid " + themeConfig.colorPrimary);
            } else {
                this->setStyleQss("background-color", themeConfig.colorDisabled);
                this->setStyleQss("border", "1px  solid " + themeConfig.colorDisabledBorder);
            }

            this->setStyleSheet(this->getJoinStyles());
            return;
        }
        painter.setRenderHint(QPainter::Antialiasing, true);
        QPen pen;
        pen.setColor(Qt::white);
        pen.setWidth(2);
        painter.setPen(pen);
        pen.setJoinStyle(Qt::MiterJoin);
        auto w = this->width();
        auto h = this->height();
        auto w2 = 8;
        auto h2 = 4;
        if (state == 1) {
            if (this->isEnabled()) {
                this->setStyleQss("background-color", themeConfig.colorPrimary);
                this->setStyleQss("hover", "background-color", themeConfig.colorPrimaryHover);
                this->setStyleQss("border", "none");
                this->setStyleQss("hover", "border", "none");
            } else {
                this->setStyleQss("background-color", themeConfig.colorDisabled);
                this->setStyleQss("border", "1px  solid " + themeConfig.colorDisabledBorder);
                pen.setColor(Util::fromCssColor(themeConfig.colorTextDisabled));
                painter.setPen(pen);
            }


            this->setStyleSheet(this->getJoinStyles());
            // 旋转和平移都是针对坐标系的
            painter.translate(w / 2, h / 2);
            painter.rotate(-45);
            painter.drawLine(QPoint(-w2 / 2, -h2 / 2), QPoint(-w2 / 2, h2 / 2));
            painter.drawLine(QPoint(-w2 / 2, h2 / 2), QPoint(w2 / 2, h2 / 2));
            return;
        }
        if (state == 2) {
            auto brush = QBrush();
            brush.setColor(Util::fromCssColor(themeConfig.colorPrimary));
            if (this->isEnabled()) {
                this->setStyleQss("background-color", "none");
                this->setStyleQss("hover", "background-color", "none");
                this->setStyleQss("border", "1px  solid " + themeConfig.colorDisabledBorder);
                this->setStyleQss("hover", "border", "1px  solid " + themeConfig.colorPrimary);
            } else {
                this->setStyleQss("background-color", "none");
                this->setStyleQss("border", "1px  solid " + themeConfig.colorTextDisabled);
                brush.setColor(Util::fromCssColor(themeConfig.colorTextDisabled));
            }
            this->setStyleSheet(this->getJoinStyles());
            brush.setStyle(Qt::SolidPattern);
            painter.setBrush(brush);
            painter.drawRect(QRect(w / 4 - 1, h / 4 - 1, w / 2 + 2, h / 2 + 2));
            return;
        }


    }

    int RectCheck::getState() const {
        return state;
    }


    CheckBox::CheckBox(const CheckBoxAttr &attr, QWidget *parent) : attr(attr), QWidget(parent) {
        auto *layout = new QHBoxLayout();
        layout->setMargin(0);
        layout->setSpacing(0);
        this->setLayout(layout);
        auto themeConfig = ThemeConfig::Instance();
        QFont font;
        font.setPixelSize(themeConfig.fontSize);

        auto *check = new RectCheck();
        check->setMinimumWidth(16);
        check->setFixedSize(16, 16);
        if (this->attr.defaultChecked || this->attr.checked) {
            check->setState(1);
        } else if (this->attr.indeterminate) {
            check->setState(2);
        }
        check->setDisabled(this->attr.disabled);
        connect(check, SIGNAL(clicked()), this, SLOT(onClicked()));

        auto textAttr = TextAttr();
        textAttr.fontSize = 16;
        auto *label = new Text(this->attr.text, textAttr);

//        label->setFont(font);
//        label->setStyleSheet("padding-left:8px;padding-right:8px;");
        label->setDisabled(this->attr.disabled);
        auto widget = new HWidget(this, true);
        widget->addWidget(label);
        widget->setStyleSheet("padding-left:8px;padding-right:8px;");
//        LOG_INFO("widget")
//        LOG_INFO(widget)
        connect(widget, SIGNAL(clicked()), this, SLOT(onClicked()));
        layout->addWidget(check);
        layout->addWidget(widget);
        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    void CheckBox::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
    }

    void CheckBox::onClicked() {
        LOG_INFO(sender())
        auto obj = dynamic_cast<RectCheck *>(this->layout()->itemAt(0)->widget());
        if (obj) {
            if (obj->getState() == 2 || obj->getState() == 0) {
                obj->setState(1);
            } else {
                obj->setState(0);
            }
        }
        LOG_INFO("onClicked")
    }

    CheckBoxGroup::CheckBoxGroup(const CheckBoxGroupAttr &attr, QWidget *parent) : QWidget(parent), attr(attr) {
        auto *layout = new QHBoxLayout();
        layout->setMargin(0);
        layout->setSpacing(0);
        this->setLayout(layout);
        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        auto *wi = new HWidget(nullptr, true);
        layout->addWidget(wi);

        for (int index = 0; index < this->attr.options.size(); index++) {
            auto *tmp = new HWidget();
            if (index == this->attr.options.size() - 1) {
            } else {
                tmp->setStyleSheet("HWidget::{margin-right:10px}");
            }
//            tmp->addWidget(new CheckBox(this->attr.options[index].label));
            tmp->addWidget(new CheckBox(CheckBoxAttr(this->attr.options[index].label)));
            wi->addWidget(tmp);
        }
//        this->setStyleSheet("border: 1px solid red;");
    }
}