#include "Radio.h"
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


    RoundRadio::RoundRadio(QWidget *parent) : QWidget(parent) {
        this->setFixedSize(16, 16);
        auto w = this->width();
        auto themeConfig = ThemeConfig::Instance();
        this->setStyleQss("border-radius", std::to_string(w / 2) + "px");
//            this->setStyleQss("hover", "background-color", themeConfig.colorPrimary);
        this->setStyleQss("border", "1px  solid " + themeConfig.colorDisabledBorder);
        this->setStyleQss("hover", "border", "1px  solid " + themeConfig.colorPrimary);
        this->setStyleSheet(this->getJoinStyles());
    }

    void RoundRadio::paintEvent(QPaintEvent *event) {
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
        painter.setRenderHints(QPainter::SmoothPixmapTransform, true);//平滑处理
        QPen pen;
        pen.setJoinStyle(Qt::MiterJoin);
        auto w = this->width();
        auto h = this->height();
        auto w2 = 6;
        auto h2 = 6;
        if (state == 1) {
            auto brush = QBrush();
            if (this->isEnabled()) {
                this->setStyleQss("background-color", themeConfig.colorPrimary);
                this->setStyleQss("hover", "background-color", themeConfig.colorPrimaryHover);
                this->setStyleQss("border", "none");
                this->setStyleQss("hover", "border", "none");
                pen.setColor(Qt::white);
                pen.setWidth(1);
                painter.setPen(pen);
                brush.setColor(Qt::white);
            } else {
                this->setStyleQss("background-color", themeConfig.colorDisabled);
                this->setStyleQss("border", "1px  solid " + themeConfig.colorDisabledBorder);
                pen.setColor(Util::fromCssColor(themeConfig.colorTextDisabled));
                pen.setWidth(1);
                painter.setPen(pen);
                brush.setColor(Util::fromCssColor(themeConfig.colorTextDisabled));
                w2 = 8;
                h2 = 8;
            }
            this->setStyleSheet(this->getJoinStyles());
            brush.setStyle(Qt::SolidPattern);
            painter.setBrush(brush);
            painter.translate(w / 2, h / 2);
            painter.drawEllipse(QRect(-w2 / 2, -h2 / 2, w2, h2));
//            LOG_INFO("w:" << w << "," << h)
//            LOG_INFO("w2:" << w2 << "," << h2)
            return;
        }
    }

    int RoundRadio::getState() const {
        return state;
    }


    Radio::Radio(const RadioAttr &attr, QWidget *parent) : attr(attr), QWidget(parent) {
        auto *layout = new QHBoxLayout();
        layout->setMargin(0);
        layout->setSpacing(0);
        this->setLayout(layout);
        auto themeConfig = ThemeConfig::Instance();
        QFont font;
        font.setPixelSize(themeConfig.fontSize);

        auto *check = new RoundRadio();
        check->setMinimumWidth(16);
        check->setFixedSize(16, 16);
        if (this->attr.defaultChecked || this->attr.checked) {
            check->setState(1);
        }
        check->setDisabled(this->attr.disabled);
        connect(check, SIGNAL(clicked()), this, SLOT(onClicked()));
        layout->addWidget(check);
        if (!this->attr.text.isEmpty()) {
            auto widget = new HWidget(this, true);
            auto textAttr = TextAttr();
            textAttr.fontSize = 16;
            auto *label = new Text(this->attr.text, textAttr);
            label->setDisabled(this->attr.disabled);
            widget->addWidget(label);
            widget->setContentsMargins(8, 0, 8, 0);
            connect(widget, SIGNAL(clicked()), this, SLOT(onClicked()));
            layout->addWidget(widget);
        }
        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    void Radio::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
    }

    void Radio::onClicked() {
        LOG_INFO(sender())
        auto obj = dynamic_cast<RoundRadio *>(this->layout()->itemAt(0)->widget());
        if (obj) {
            if (obj->getState() == 2 || obj->getState() == 0) {
                obj->setState(1);
            } else {
                obj->setState(0);
            }
        }
        LOG_INFO("onClicked")
    }

    RadioGroup::RadioGroup(const RadioGroupAttr &attr, QWidget *parent) : QWidget(parent), attr(attr) {
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
            tmp->addWidget(new Radio(RadioAttr(this->attr.options[index].label)));
            wi->addWidget(tmp);
        }
    }
}