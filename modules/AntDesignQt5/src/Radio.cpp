#include "Radio.h"

#include <utility>
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


    Radio::Radio(const QString &text, QWidget *parent) : attrText(text), QWidget(parent) {
        auto *layout = new QHBoxLayout();
        layout->setMargin(0);
        layout->setSpacing(0);
        this->setLayout(layout);
        auto themeConfig = ThemeConfig::Instance();
        QFont font;
        font.setPixelSize(themeConfig.fontSize);

        roundRadio_ = new RoundRadio();
        roundRadio_->setMinimumWidth(16);
        roundRadio_->setFixedSize(16, 16);
        /*if (this->attr.defaultChecked || this->attr.checked) {
            roundRadio_->setState(1);
        }
        roundRadio_->setDisabled(this->attr.disabled);*/
        connect(roundRadio_, SIGNAL(clicked()), this, SLOT(onClicked()));
        layout->addWidget(roundRadio_);

        text_ = new Text(this->attrText);
        textWidget_ = new HWidget();
        textWidget_->setContentsMargins(8, 0, 0, 0);
        textWidget_->addWidget(text_);
        connect(textWidget_, SIGNAL(clicked()), this, SLOT(onClicked()));
        layout->addWidget(textWidget_);
        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        this->updateAttr();
    }

    void Radio::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
    }

    void Radio::onClicked() {
        if (this->attrDisabled) {
            return;
        }
        auto obj = dynamic_cast<RoundRadio *>(this->layout()->itemAt(0)->widget());
        if (obj) {
            if (obj->getState() == 0) {
                obj->setState(1);
                this->attrChecked = true;
                emit onChange(obj->getState() == 1);
            } else {
                // obj->setState(0);
            }
        }
    }

    void Radio::setAttrChecked(bool checked) {
        Radio::attrChecked = checked;
        this->updateAttr();
    }

    void Radio::setAttrDefaultChecked(bool defaultChecked) {
        Radio::attrDefaultChecked = defaultChecked;
        this->updateAttr();
    }

    void Radio::setAttrDisabled(bool disabled) {
        Radio::attrDisabled = disabled;
        this->updateAttr();
    }

    void Radio::setAttrText(const QString &text) {
        Radio::attrText = text;
        this->updateAttr();
    }

    void Radio::updateAttr() {
        if (this->attrChecked.has_value()) {
            this->roundRadio_->setState(this->attrChecked.value() ? 1 : 0);
        } else {
            this->roundRadio_->setState(this->attrDefaultChecked ? 1 : 0);
        }

        this->textWidget_->setVisible(!this->attrText.isEmpty());
        this->text_->setText(this->attrText);
        this->roundRadio_->setDisabled(this->attrDisabled);
        this->text_->setDisabled(this->attrDisabled);
    }

    const QString &Radio::getAttrText() const {
        return attrText;
    }

    RadioGroup::RadioGroup(const std::vector<GeneralAttrOption> &attrOptions, QString attrValue, QWidget *parent) :
            QWidget(parent), attrValue(std::move(attrValue)), attrOptions(attrOptions) {
        auto *layout = new QHBoxLayout();
        layout->setMargin(0);
        layout->setSpacing(0);
        this->setLayout(layout);
        layout->setAlignment(Qt::AlignLeft);
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        auto *wi = new HWidget(nullptr, true);
        layout->addWidget(wi);

        for (int index = 0; index < this->attrOptions.size(); index++) {
            auto *tmp = new HWidget();
            if (index == attrOptions.size() - 1) {
            } else {
                tmp->setContentsMargins(0, 0, 10, 0);
            }
            auto *radio = new Radio(this->attrOptions[index].label);
            this->radioList_.push_back(radio);
            connect(radio, &Radio::onChange, this, [radio, this](bool checked) {
                if (checked) {
                    for (auto it: this->radioList_) {
                        if ((*it).getAttrText() != radio->getAttrText()) {
                            it->setAttrChecked(false);
                        }
                    }
                }
                emit onChange(radio->getAttrText());
            });
            tmp->addWidget(radio);
            wi->addWidget(tmp);
        }
    }
}