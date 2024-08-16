//
///7/1.
//

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



    const InputAttr &Input::getAttr() const {
        return attr;
    }

    void Input::setAttr(const InputAttr &inputAttr) {
        QLayout *layout = new QHBoxLayout(this);
        layout->setMargin(0);
        layout->setSpacing(0);

        auto themeConfig = InputConfig::Instance();
//        LOG_INFO("---------------------------------------")

        auto *beforeWidget = new HWidget(this);
        auto *afterWidget = new HWidget(this);

        auto inputAWidget = AWidget();
        auto buttonAWidget = AWidget();
        editWidget = new HWidget();

        beforeWidget->setStyleQss("border-radius", "none");
        afterWidget->setStyleQss("border-radius", "none");
        inputAWidget.setStyleQss("border-radius", "none");
        buttonAWidget.setStyleQss("border-radius", "none");
        editWidget->setStyleQss("border-radius", "none");
        auto *edit = new WLQLineEdit(this);


        connect(edit, SIGNAL(focusChange(QFocusEvent * )), this, SLOT(editFocusChange(QFocusEvent * )));
        QFont font;

        this->attr = inputAttr;

        auto sizeHeight = themeConfig.controlHeight;
        if (this->attr.size == GeneralAttrSize::large) {
            font.setPixelSize(themeConfig.inputFontSizeLG);

            sizeHeight = themeConfig.controlHeightLG;
            this->setStyleQss("padding-top", std::to_string(themeConfig.paddingBlockLG) + "px");
            this->setStyleQss("padding-bottom", std::to_string(themeConfig.paddingBlockLG) + "px");
            editWidget->setStyleQss("padding-left", std::to_string(themeConfig.paddingInlineLG) + "px");
            editWidget->setStyleQss("padding-right", std::to_string(themeConfig.paddingInlineLG) + "px");
            editWidget->setContentsMargins(themeConfig.paddingInlineLG, themeConfig.paddingBlockLG, themeConfig.paddingInlineLG, themeConfig.paddingBlockLG);

        } else if (this->attr.size == GeneralAttrSize::small) {
            font.setPixelSize(themeConfig.inputFontSizeSM);
            sizeHeight = themeConfig.controlHeightSM;
            this->setStyleQss("padding-top", std::to_string(themeConfig.paddingBlockSM) + "px");
            this->setStyleQss("padding-bottom", std::to_string(themeConfig.paddingBlockSM) + "px");
            editWidget->setStyleQss("padding-left", std::to_string(themeConfig.paddingInlineSM) + "px");
            editWidget->setStyleQss("padding-right", std::to_string(themeConfig.paddingInlineSM) + "px");
            editWidget->setContentsMargins(themeConfig.paddingInlineSM, themeConfig.paddingBlockSM, themeConfig.paddingInlineSM, themeConfig.paddingBlockSM);

        } else {
            font.setPixelSize(themeConfig.inputFontSize);

            this->setStyleQss("padding-top", std::to_string(themeConfig.paddingBlock) + "px");
            this->setStyleQss("padding-bottom", std::to_string(themeConfig.paddingBlock) + "px");
            editWidget->setStyleQss("padding-left", std::to_string(themeConfig.paddingInline) + "px");
            editWidget->setStyleQss("padding-right", std::to_string(themeConfig.paddingInline) + "px");
            editWidget->setContentsMargins(themeConfig.paddingInline, themeConfig.paddingBlock, themeConfig.paddingInline, themeConfig.paddingBlock);

        }

        this->setStyleQss("height", std::to_string(sizeHeight));
        this->setFixedHeight(sizeHeight);

        if (attr.variant == InputAttrVariant::outlined) {
            if (attr.status == InputAttrStatus::none) {
                beforeWidget->setStyleQss("border-style", "solid");
                beforeWidget->setStyleQss("border-width", "1px 0px 1px 1px");
                beforeWidget->setStyleQss("border-color", themeConfig.colorBorder);

                afterWidget->setStyleQss("border-style", "solid");
                afterWidget->setStyleQss("border-width", "1px 1px 1px 0px");
                afterWidget->setStyleQss("border-color", themeConfig.colorBorder);


                editWidget->setStyleQss("border", "1px solid " + themeConfig.colorBorder);
                editWidget->setStyleQss("hover", "border", "1px solid " + themeConfig.hoverBorderColor);
                editWidget->setStyleQss("focus", "border", "1px solid " + themeConfig.activeBorderColor);
            } else if (attr.status == InputAttrStatus::warning) {

            } else if (attr.status == InputAttrStatus::error) {

            }
        } else if (attr.variant == InputAttrVariant::borderless) {
            beforeWidget->setStyleQss("border", "none");
            afterWidget->setStyleQss("border", "none");
            editWidget->setStyleQss("border", "none");
        } else if (attr.variant == InputAttrVariant::filled) {
            this->layout()->setMargin(0);
            beforeWidget->setStyleQss("border", "none");
            afterWidget->setStyleQss("border", "none");
            editWidget->setStyleQss("border", "none");

//            this->setStyleQss("background-color", themeConfig.colorDisabled);
//            this->setStyleQss("hover", "background-color", "none");

//            labelAWidget.setStyleQss("background-color", themeConfig.colorDisabled);
//            labelAWidget.setStyleQss("hover", "background-color", "none");
//
            editWidget->setStyleQss("background-color", themeConfig.colorInputFilledBG);
            editWidget->setStyleQss("hover", "background-color", themeConfig.colorInputFilledHoverBG);

            inputAWidget.setStyleQss("background-color", themeConfig.colorInputFilledBG);
            inputAWidget.setStyleQss("hover", "background-color", themeConfig.colorInputFilledHoverBG);
//            inputAWidget.setStyleQss("focus", "background-color", "none");
        }

        if (attr.addonBefore != nullptr) {
            beforeWidget->addWidget(attr.addonBefore);
            beforeWidget->setStyleQss("border-top-left-radius", std::to_string(themeConfig.borderRadius) + "px");
            beforeWidget->setStyleQss("border-bottom-left-radius", std::to_string(themeConfig.borderRadius) + "px");
            beforeWidget->setStyleQss("background-color", themeConfig.addonBg);


            beforeWidget->setStyleSheet(beforeWidget->getJoinStyles());

            beforeWidget->setFont(font);
            layout->addWidget(beforeWidget);
        } else {
            editWidget->setStyleQss("border-top-left-radius", std::to_string(themeConfig.borderRadius) + "px");
            editWidget->setStyleQss("border-bottom-left-radius", std::to_string(themeConfig.borderRadius) + "px");
        }
        editWidget->layout()->setMargin(2);
        layout->addWidget(editWidget);
        editWidget->enterEventCB = [this](QEvent *event) -> void {
            auto themeConfig = InputConfig::Instance();
            if (editWidget->layout() != nullptr) {
                QLayoutItem *child;
                auto count = editWidget->layout()->count();
                for (int index = 0; index < count; index++) {
                    child = editWidget->layout()->itemAt(index);
                    if (child && child->widget()) {
                        if (this->attr.variant == InputAttrVariant::filled) {
                            child->widget()->setStyleSheet(QString::fromStdString(":!hover{background-color:" + themeConfig.colorInputFilledHoverBG + ";padding:0;"
                                                                                                                                                      "}:hover{background-color:" +
                                                                                  themeConfig.colorInputFilledHoverBG + ";padding:0;"
                                                                                                                        "}"));
                            editWidget->setStyleSheet(editWidget->getJoinStyles());
                        } else {
                            child->widget()->setStyleSheet(QString::fromStdString(":!hover{border:none;padding:0;}:hover{border:none;padding:0;}"));
                            editWidget->setStyleSheet(editWidget->getJoinStyles());
                        }

                    }
                }
            }
        };
        editWidget->leaveEventCB = [this](QEvent *event) -> void {
            auto themeConfig = InputConfig::Instance();
            if (editWidget->layout() != nullptr) {
                QLayoutItem *child;
                auto count = editWidget->layout()->count();
                for (int index = 0; index < count; index++) {
                    child = editWidget->layout()->itemAt(index);
                    if (child && child->widget()) {
                        if (this->attr.variant == InputAttrVariant::filled) {
                            if (!this->editFocus) {
                                child->widget()->setStyleSheet(QString::fromStdString(":!hover{background-color:" + themeConfig.colorInputFilledBG + ";padding:0;"
                                                                                                                                                     "}:hover{background-color:" +
                                                                                      themeConfig.colorInputFilledBG + ";padding:0;"
                                                                                                                       "}"));
                                this->editWidget->setStyleQss("background-color", themeConfig.colorInputFilledBG);
                                this->editWidget->setStyleQss("hover", "background-color", themeConfig.colorInputFilledHoverBG);
                                this->editWidget->setStyleSheet(editWidget->getJoinStyles());
                            }
                        }else{
                            this->editWidget->setStyleSheet(editWidget->getJoinStyles());
                        }

                    }
                }
            }
        };

        if (attr.prefix) {
            attr.prefix->setFixedSize(16, 16);
            auto tmp = new HWidget(editWidget);
            tmp->addWidget(attr.prefix);
            tmp->setFixedSize(16, 16);
            editWidget->addWidget(tmp);
//            editWidget->addWidget(attr.prefix);
        }

        edit->setFont(font);
        edit->setPlaceholderText(attr.placeholder);
        inputAWidget.setStyleQss("border", "none");
        inputAWidget.setStyleQss("padding", "0px");
        edit->setStyleSheet(inputAWidget.getJoinStyles());

        editWidget->addWidget(edit);
        if (attr.suffix) {
            auto tmp = new HWidget();
            attr.suffix->setFixedSize(16, 16);
            tmp->addWidget(attr.suffix);
            tmp->setFixedSize(16, 16);
            editWidget->addWidget(tmp);
        }

        if (this->attr.addonAfter != nullptr) {
            afterWidget->addWidget(attr.addonAfter);
            afterWidget->setStyleQss("border-top-right-radius", std::to_string(themeConfig.borderRadius) + "px");
            afterWidget->setStyleQss("border-bottom-right-radius", std::to_string(themeConfig.borderRadius) + "px");
            afterWidget->setStyleQss("background-color", themeConfig.addonBg);
            afterWidget->setStyleSheet(afterWidget->getJoinStyles());
            afterWidget->setFont(font);

            layout->addWidget(afterWidget);
        } else {
            editWidget->setStyleQss("border-top-right-radius", std::to_string(themeConfig.borderRadius) + "px");
            editWidget->setStyleQss("border-bottom-right-radius", std::to_string(themeConfig.borderRadius) + "px");
        }
        editWidget->setStyleSheet(editWidget->getJoinStyles());

//        layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Minimum));
        this->setLayout(layout);
        this->setStyleQss("border-radius", std::to_string(themeConfig.borderRadius) + "px");
        this->setStyleSheet(this->getJoinStyles());
    }

    Input::Input(const InputAttr &inputAttr, QWidget *parent) : QWidget(parent) {
        this->setAttr(inputAttr);
    }

    void Input::editFocusChange(QFocusEvent *e) {
        auto themeConfig = InputConfig::Instance();
        this->editFocus = e->gotFocus();
        if (e->gotFocus()) {
            if (this->attr.variant == InputAttrVariant::filled) {
                auto *edit = dynamic_cast<QWidget *>(sender());
                if (edit) {
                    this->editWidget->setStyleQss("background-color", "none");
                    this->editWidget->setStyleQss("hover", "background-color", "none");
                    this->editWidget->setStyleSheet(this->editWidget->getJoinStyles());
                    edit->setStyleSheet(":!hover{background-color:none;padding:0;}:hover{background-color:none;padding:0;}");
                }
            }
        } else {
            if (this->attr.variant == InputAttrVariant::filled) {
                auto *edit = dynamic_cast<QWidget *>(sender());
                if (edit) {
                    edit->setStyleSheet(
                            ":!hover{background-color:" + QString::fromStdString(themeConfig.colorInputFilledBG) + ";padding:0;}:hover{background-color:none;padding:0;}");
                }
                this->editWidget->setStyleQss("background-color", themeConfig.colorInputFilledBG);
                this->editWidget->setStyleQss("hover", "background-color", themeConfig.colorInputFilledHoverBG);
                this->editWidget->setStyleSheet(this->editWidget->getJoinStyles());
            }
//            LOG_INFO("no")
        }

    }

}

