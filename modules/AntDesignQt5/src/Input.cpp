#include <QSpacerItem>
#include <QHBoxLayout>
#include "Input.h"
#include "QLineEdit"
#include "ThemeConfig.h"
#include "QLabel"
#include "QPushButton"
#include "HWidget.h"
#include "WLQLineEdit.h"

namespace wl {
    Input::Input(QWidget *parent) : QWidget(parent) {
        QLayout *layout = new QHBoxLayout(this);
        layout->setMargin(0);
        layout->setSpacing(0);
        this->setLayout(layout);

        beforeWidget_ = new HWidget(this);
        afterWidget_ = new HWidget(this);
        editWidget_ = new HWidget();
        edit_ = new WLQLineEdit(this);

        prefixWidget_ = new HWidget(this);
        suffixWidget_ = new HWidget(this);
        editWidget_->addWidget(prefixWidget_);
        editWidget_->addWidget(edit_);
        editWidget_->addWidget(suffixWidget_);
        this->layout()->addWidget(beforeWidget_);
        this->layout()->addWidget(editWidget_);
        this->layout()->addWidget(afterWidget_);
    }


    void Input::editFocusChange(QFocusEvent *e) {
        auto themeConfig = InputConfig::Instance();
        this->editFocus = e->gotFocus();
        if (e->gotFocus()) {
            if (this->attrVariant == InputAttrVariant::filled) {
                auto *edit = dynamic_cast<QWidget *>(sender());
                if (edit) {
                    this->editWidget_->setStyleQss("background-color", "none");
                    this->editWidget_->setStyleQss("hover", "background-color", "none");
                    this->editWidget_->setStyleSheet(this->editWidget_->getJoinStyles());
                    edit->setStyleSheet(":!hover{background-color:none;padding:0;}:hover{background-color:none;padding:0;}");
                }
            }
        } else {
            if (this->attrVariant == InputAttrVariant::filled) {
                auto *edit = dynamic_cast<QWidget *>(sender());
                if (edit) {
                    edit->setStyleSheet(
                            ":!hover{background-color:" + QString::fromStdString(themeConfig.colorInputFilledBG) + ";padding:0;}:hover{background-color:none;padding:0;}");
                }
                this->editWidget_->setStyleQss("background-color", themeConfig.colorInputFilledBG);
                this->editWidget_->setStyleQss("hover", "background-color", themeConfig.colorInputFilledHoverBG);
                this->editWidget_->setStyleSheet(this->editWidget_->getJoinStyles());
            }
        }
    }

    QSize Input::sizeHint() const {
        auto size1 = QWidget::sizeHint();
        return size1;
    }

    void Input::updateAttr() {
        auto themeConfig = InputConfig::Instance();
        auto inputAWidget = AWidget();
        auto buttonAWidget = AWidget();

        beforeWidget_->setStyleQss("border-radius", "none");
        afterWidget_->setStyleQss("border-radius", "none");
        inputAWidget.setStyleQss("border-radius", "none");
        buttonAWidget.setStyleQss("border-radius", "none");
        this->editWidget_->setStyleQss("border-radius", "none");
        edit_->setText("");

        connect(edit_, SIGNAL(focusChange(QFocusEvent * )), this, SLOT(editFocusChange(QFocusEvent * )));
        connect(edit_, &WLQLineEdit::textChanged, this, [this](const QString &text) {
            emit textChanged(text);
        });
        QFont font;


        auto sizeHeight = themeConfig.controlHeight;
        if (this->attrSize == GeneralAttrSize::large) {
            font.setPixelSize(themeConfig.inputFontSizeLG);

            sizeHeight = themeConfig.controlHeightLG;
            this->setStyleQss("padding-top", std::to_string(themeConfig.paddingBlockLG) + "px");
            this->setStyleQss("padding-bottom", std::to_string(themeConfig.paddingBlockLG) + "px");
            this->editWidget_->setStyleQss("padding-left", std::to_string(themeConfig.paddingInlineLG) + "px");
            this->editWidget_->setStyleQss("padding-right", std::to_string(themeConfig.paddingInlineLG) + "px");
            this->editWidget_->setContentsMargins(themeConfig.paddingInlineLG, themeConfig.paddingBlockLG, themeConfig.paddingInlineLG, themeConfig.paddingBlockLG);

        } else if (this->attrSize == GeneralAttrSize::small) {
            font.setPixelSize(themeConfig.inputFontSizeSM);
            sizeHeight = themeConfig.controlHeightSM;
            this->setStyleQss("padding-top", std::to_string(themeConfig.paddingBlockSM) + "px");
            this->setStyleQss("padding-bottom", std::to_string(themeConfig.paddingBlockSM) + "px");
            this->editWidget_->setStyleQss("padding-left", std::to_string(themeConfig.paddingInlineSM) + "px");
            this->editWidget_->setStyleQss("padding-right", std::to_string(themeConfig.paddingInlineSM) + "px");
            this->editWidget_->setContentsMargins(themeConfig.paddingInlineSM, themeConfig.paddingBlockSM, themeConfig.paddingInlineSM, themeConfig.paddingBlockSM);

        } else {
            font.setPixelSize(themeConfig.inputFontSize);

            this->setStyleQss("padding-top", std::to_string(themeConfig.paddingBlock) + "px");
            this->setStyleQss("padding-bottom", std::to_string(themeConfig.paddingBlock) + "px");
            this->editWidget_->setStyleQss("padding-left", std::to_string(themeConfig.paddingInline) + "px");
            this->editWidget_->setStyleQss("padding-right", std::to_string(themeConfig.paddingInline) + "px");
            this->editWidget_->setContentsMargins(themeConfig.paddingInline, themeConfig.paddingBlock, themeConfig.paddingInline, themeConfig.paddingBlock);

        }

        this->setStyleQss("height", std::to_string(sizeHeight));
        this->setFixedHeight(sizeHeight);

        if (attrVariant == InputAttrVariant::outlined) {
            if (attrStatus == InputAttrStatus::none) {
                beforeWidget_->setStyleQss("border-style", "solid");
                beforeWidget_->setStyleQss("border-width", "1px 0px 1px 1px");
                beforeWidget_->setStyleQss("border-color", themeConfig.colorBorder);

                afterWidget_->setStyleQss("border-style", "solid");
                afterWidget_->setStyleQss("border-width", "1px 1px 1px 0px");
                afterWidget_->setStyleQss("border-color", themeConfig.colorBorder);


                this->editWidget_->setStyleQss("border", "1px solid " + themeConfig.colorBorder);
                this->editWidget_->setStyleQss("hover", "border", "1px solid " + themeConfig.hoverBorderColor);
                this->editWidget_->setStyleQss("focus", "border", "1px solid " + themeConfig.activeBorderColor);
            } else if (attrStatus == InputAttrStatus::warning) {

            } else if (attrStatus == InputAttrStatus::error) {

            }
        } else if (attrVariant == InputAttrVariant::borderless) {
            beforeWidget_->setStyleQss("border", "none");
            afterWidget_->setStyleQss("border", "none");
            this->editWidget_->setStyleQss("border", "none");
        } else if (attrVariant == InputAttrVariant::filled) {
            this->layout()->setMargin(0);
            beforeWidget_->setStyleQss("border", "none");
            afterWidget_->setStyleQss("border", "none");
            this->editWidget_->setStyleQss("border", "none");

//            this->setStyleQss("background-color", themeConfig.colorDisabled);
//            this->setStyleQss("hover", "background-color", "none");

//            labelAWidget.setStyleQss("background-color", themeConfig.colorDisabled);
//            labelAWidget.setStyleQss("hover", "background-color", "none");
//
            this->editWidget_->setStyleQss("background-color", themeConfig.colorInputFilledBG);
            this->editWidget_->setStyleQss("hover", "background-color", themeConfig.colorInputFilledHoverBG);

            inputAWidget.setStyleQss("background-color", themeConfig.colorInputFilledBG);
            inputAWidget.setStyleQss("hover", "background-color", themeConfig.colorInputFilledHoverBG);
//            inputAWidget.setStyleQss("focus", "background-color", "none");
        }

        if (attrAddonBefore != nullptr) {
            beforeWidget_->addWidget(attrAddonBefore);
            beforeWidget_->setStyleQss("border-top-left-radius", std::to_string(themeConfig.borderRadius) + "px");
            beforeWidget_->setStyleQss("border-bottom-left-radius", std::to_string(themeConfig.borderRadius) + "px");
            beforeWidget_->setStyleQss("background-color", themeConfig.addonBg);


            beforeWidget_->setStyleSheet(beforeWidget_->getJoinStyles());

            beforeWidget_->setFont(font);
        } else {
            this->editWidget_->setStyleQss("border-top-left-radius", std::to_string(themeConfig.borderRadius) + "px");
            this->editWidget_->setStyleQss("border-bottom-left-radius", std::to_string(themeConfig.borderRadius) + "px");
        }
        this->editWidget_->layout()->setMargin(2);
        this->editWidget_->enterEventCB = [this](QEvent *event) -> void {
            auto themeConfig = InputConfig::Instance();
            if (this->editWidget_->layout() != nullptr) {
                QLayoutItem *child;
                auto count = this->editWidget_->layout()->count();
                for (int index = 0; index < count; index++) {
                    child = this->editWidget_->layout()->itemAt(index);
                    if (child && child->widget()) {
                        if (this->attrVariant == InputAttrVariant::filled) {
                            child->widget()->setStyleSheet(QString::fromStdString(":!hover{background-color:" + themeConfig.colorInputFilledHoverBG + ";padding:0;"
                                                                                                                                                      "}:hover{background-color:" +
                                                                                  themeConfig.colorInputFilledHoverBG + ";padding:0;"
                                                                                                                        "}"));
                            this->editWidget_->setStyleSheet(this->editWidget_->getJoinStyles());
                        } else {
                            child->widget()->setStyleSheet(QString::fromStdString(":!hover{border:none;padding:0;}:hover{border:none;padding:0;}"));
                            this->editWidget_->setStyleSheet(this->editWidget_->getJoinStyles());
                        }

                    }
                }
            }
        };
        this->editWidget_->leaveEventCB = [this](QEvent *event) -> void {
            auto themeConfig = InputConfig::Instance();
            if (this->editWidget_->layout() != nullptr) {
                QLayoutItem *child;
                auto count = this->editWidget_->layout()->count();
                for (int index = 0; index < count; index++) {
                    child = this->editWidget_->layout()->itemAt(index);
                    if (child && child->widget()) {
                        if (this->attrVariant == InputAttrVariant::filled) {
                            if (!this->editFocus) {
                                child->widget()->setStyleSheet(QString::fromStdString(":!hover{background-color:" + themeConfig.colorInputFilledBG + ";padding:0;"
                                                                                                                                                     "}:hover{background-color:" +
                                                                                      themeConfig.colorInputFilledBG + ";padding:0;"
                                                                                                                       "}"));
                                this->editWidget_->setStyleQss("background-color", themeConfig.colorInputFilledBG);
                                this->editWidget_->setStyleQss("hover", "background-color", themeConfig.colorInputFilledHoverBG);
                                this->editWidget_->setStyleSheet(this->editWidget_->getJoinStyles());
                            }
                        } else {
                            this->editWidget_->setStyleSheet(this->editWidget_->getJoinStyles());
                        }

                    }
                }
            }
        };

//        if (attrPrefix) {
//            attrPrefix->setFixedSize(16, 16);
//            auto tmp = new HWidget(editWidget_);
//            tmp->addWidget(attrPrefix);
//            tmp->setFixedSize(16, 16);
//            this->editWidget_->addWidget(tmp);
//        }

        edit_->setFont(font);
        edit_->setPlaceholderText(attrPlaceholder);
        inputAWidget.setStyleQss("border", "none");
        inputAWidget.setStyleQss("padding", "0px");
        edit_->setStyleSheet(inputAWidget.getJoinStyles());

//        if (attrSuffix) {
//            auto tmp = new HWidget();
//            attrSuffix->setFixedSize(16, 16);
//            tmp->addWidget(attrSuffix);
//            tmp->setFixedSize(16, 16);
//            this->editWidget_->addWidget(tmp);
//        }

        if (this->attrAddonAfter != nullptr) {
            afterWidget_->addWidget(attrAddonAfter);
            afterWidget_->setStyleQss("border-top-right-radius", std::to_string(themeConfig.borderRadius) + "px");
            afterWidget_->setStyleQss("border-bottom-right-radius", std::to_string(themeConfig.borderRadius) + "px");
            afterWidget_->setStyleQss("background-color", themeConfig.addonBg);
            afterWidget_->setStyleSheet(afterWidget_->getJoinStyles());
            afterWidget_->setFont(font);
        } else {
            this->editWidget_->setStyleQss("border-top-right-radius", std::to_string(themeConfig.borderRadius) + "px");
            this->editWidget_->setStyleQss("border-bottom-right-radius", std::to_string(themeConfig.borderRadius) + "px");
        }
        this->editWidget_->setStyleSheet(this->editWidget_->getJoinStyles());
        this->setStyleQss("border-radius", std::to_string(themeConfig.borderRadius) + "px");
        this->setStyleSheet(this->getJoinStyles());
    }

    void Input::setAttrSize(GeneralAttrSize generalAttrSize) {
        Input::attrSize = generalAttrSize;
    }

    void Input::setAttrAddonBefore(QWidget *addonBefore) {
        Input::attrAddonBefore = addonBefore;
    }

    void Input::setAttrAddonAfter(QWidget *addonAfter) {
        Input::attrAddonAfter = addonAfter;
    }

    void Input::setAttrStatus(InputAttrStatus status) {
        Input::attrStatus = status;
    }

    void Input::setAttrDisabled(bool disabled) {
        attrDisabled = disabled;
    }

    void Input::setAttrPrefix(QWidget *prefix) {
        this->editWidget_->replaceWidget(prefix, this->attrPrefix, true);
    }

    void Input::setAttrSuffix(QWidget *suffix) {
        this->editWidget_->replaceWidget(suffix, this->attrSuffix, true);
    }

    void Input::setAttrPlaceholder(const QString &placeholder) {
        Input::attrPlaceholder = placeholder;
    }

    void Input::setAttrVariant(InputAttrVariant variant) {
        Input::attrVariant = variant;
    }

    void Input::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
        this->updateAttr();
    }


}

