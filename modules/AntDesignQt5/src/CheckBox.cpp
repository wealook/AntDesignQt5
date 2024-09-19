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
        painter.setRenderHints(QPainter::SmoothPixmapTransform, true);//平滑处理

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


    CheckBox::CheckBox(QWidget *parent) : QWidget(parent) {
        auto *layout = new QHBoxLayout();
        layout->setMargin(0);
        layout->setSpacing(0);
        this->setLayout(layout);
        auto themeConfig = ThemeConfig::Instance();
        QFont font;
        font.setPixelSize((int) themeConfig.fontSize);

        rectCheck_ = new RectCheck();
        rectCheck_->setMinimumWidth(16);
        rectCheck_->setFixedSize(16, 16);

//        rectCheck_->setDisabled(this->attr.disabled);
        connect(rectCheck_, SIGNAL(clicked()), this, SLOT(onClicked()));
        layout->addWidget(rectCheck_);
        textWidget_ = new HWidget(this);
        text_ = new Text("");
//        text_->setDisabled(this->attr.disabled);
        textWidget_->addWidget(text_);
        textWidget_->setContentsMargins(8, 0, 8, 0);
        textWidget_->setStyleSheet(textWidget_->getJoinStyles());
        connect(textWidget_, SIGNAL(clicked()), this, SLOT(onClicked()));
        layout->addWidget(textWidget_);
        /*
            if (!this->attr.text.isEmpty()) {
    //            widget->setFixed();
                auto textAttr = TextAttr();
                textAttr.fontSize = 16;

            }*/
        layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    void CheckBox::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
    }

    void CheckBox::onClicked() {
        if (this->attrDisabled) {
            return;
        }
        auto obj = this->rectCheck_;
        if (obj) {
            if (obj->getState() == 2 || obj->getState() == 0) {
                obj->setState(1);
            } else {
                obj->setState(0);
            }
        }
        emit onChange(obj->getState() != 0);
    }

    void CheckBox::setAttrChecked(bool checked) {
        CheckBox::attrChecked = checked;
        this->updateAttr();
    }

    void CheckBox::setAttrDefaultChecked(bool defaultChecked) {
        CheckBox::attrDefaultChecked = defaultChecked;
        this->updateAttr();
    }

    void CheckBox::setAttrDisabled(bool disabled) {
        CheckBox::attrDisabled = disabled;
        this->updateAttr();
    }

    void CheckBox::setAttrIndeterminate(bool indeterminate) {
        CheckBox::attrIndeterminate = indeterminate;
        this->updateAttr();
    }

    void CheckBox::setAttrText(const QString &text) {
        CheckBox::attrText = text;
        this->updateAttr();
    }

    void CheckBox::updateAttr() {
        if (this->attrDefaultChecked || this->attrChecked) {
            this->rectCheck_->setState(1);
        } else if (this->attrIndeterminate) {
            this->rectCheck_->setState(2);
        }
        this->text_->setText(this->attrText);
        this->textWidget_->setVisible(!this->attrText.isEmpty());
        this->rectCheck_->setDisabled(this->attrDisabled);
        this->text_->setDisabled(this->attrDisabled);
    }

    CheckBox::CheckBox(const QString &text, QWidget *parent) : CheckBox(parent) {
        this->setAttrText(text);
    }

    const QString &CheckBox::getAttrText() const {
        return attrText;
    }

    CheckBoxGroup::CheckBoxGroup(const std::vector<GeneralAttrOption> &options, const std::vector<QString> &value, QWidget *parent)
            : QWidget(parent), attrOptions(options), attrValue(value) {
        auto *layout = new QHBoxLayout();
        layout->setMargin(0);
        layout->setSpacing(0);
        this->setLayout(layout);
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        layout->setAlignment(Qt::AlignLeft);
        for (int index = 0; index < options.size(); index++) {
            auto *tmp = new HWidget();
            if (index == options.size() - 1) {
            } else {
                tmp->setContentsMargins(0, 0, 10, 0);
            }
            auto *box = new CheckBox(options[index].label);
            connect(box, &CheckBox::onChange, this, [box, this](bool checked) {
                if (checked) {
                    bool find = std::find(this->attrValue.begin(), this->attrValue.end(), box->getAttrText()) != this->attrValue.end();
                    if (!find) {
                        this->attrValue.push_back(box->getAttrText());
                    }
                } else {
                    for (auto it = this->attrValue.begin(); it != this->attrValue.end();) {
                        if ((*it) == box->getAttrText()) {
                            it = this->attrValue.erase(it);
                        } else {
                            ++it;
                        }
                    }
                }
                emit onChange(this->attrValue);
            });
            tmp->addWidget(box);
            layout->addWidget(tmp);
        }
    }

    void CheckBoxGroup::setAttrOptions(const std::vector<GeneralAttrOption> &attrOptions) {
        CheckBoxGroup::attrOptions = attrOptions;
    }

    void CheckBoxGroup::setAttrValue(const std::vector<QString> &attrValue) {
        CheckBoxGroup::attrValue = attrValue;
    }

}