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

namespace wl {

    Input::Input(QWidget *parent) {

    }

    const InputAttr &Input::getAttr() const {
        return attr;
    }

    void Input::setAttr(const InputAttr &inputAttr) {
        QLayout *layout = new QHBoxLayout(this);
        layout->setMargin(0);
        layout->setSpacing(0);

        auto themeConfig = InputConfig::Instance();
        LOG_INFO("---------------------------------------")

        auto labelAWidget = AWidget();
        auto inputAWidget = AWidget();
        auto buttonAWidget = AWidget();
        auto *editWidget = new HWidget();
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
        std::stringstream buttonStyle;
        if (attr.status == InputAttrStatus::none) {
            labelAWidget.setStyleQss("border-style", "solid");
            labelAWidget.setStyleQss("border-width", "1px 0px 1px 1px");
            labelAWidget.setStyleQss("border-color", themeConfig.colorBorder);

            editWidget->setStyleQss("border", "1px solid " + themeConfig.colorBorder);
            editWidget->setStyleQss("hover", "border", "1px solid " + themeConfig.hoverBorderColor);
            editWidget->setStyleQss("focus", "border", "1px solid " + themeConfig.activeBorderColor);

            buttonStyle << ":!hover{ border-style:none ;background-color:  " + themeConfig.colorPrimary + " ;color:white; padding-left:5px;padding-right:5px;}";
            buttonStyle << ":hover{ border-style:none ;background-color:  " + themeConfig.colorPrimaryHover + " ; color:white;padding-left:5px;padding-right:5px;}";
        } else if (attr.status == InputAttrStatus::warning) {

        } else if (attr.status == InputAttrStatus::error) {

        }


        if (!attr.addonBefore.isEmpty()) {
            auto *label = new QLabel(this);
            label->setText(attr.addonBefore);
            label->setStyleSheet(labelAWidget.getJoinStyles());

            label->setFont(font);
//            label->setFixedHeight(themeConfig.inputFontSize + themeConfig.paddingBlock * 2);
            layout->addWidget(label);
        }
        editWidget->layout()->setMargin(2);
        layout->addWidget(editWidget);
        editWidget->enterEventCB = [editWidget](QEvent *event) -> void {
            if (editWidget->layout() != nullptr) {
                QLayoutItem *child;
                auto count = editWidget->layout()->count();
                for (int index = 0; index < count; index++) {
                    child = editWidget->layout()->itemAt(index);
                    if (child && child->widget()) {
                        LOG_INFO(child->widget()->styleSheet().toStdString())
                        child->widget()->setStyleSheet(QString::fromStdString(":!hover{border:none;padding:0;}:hover{border:none;padding:0;}"));
                        editWidget->setStyleSheet(editWidget->getJoinStyles());
                        LOG_INFO(editWidget)
                        LOG_INFO(child->widget())
                        LOG_INFO(editWidget->styleSheet().toStdString())
                    }
                }
            }
        };
        editWidget->leaveEventCB = [editWidget](QEvent *event) -> void {
        };

        if (attr.prefix) {
            attr.prefix->setFixedSize(16, 16);
            auto tmp = new HWidget(editWidget);
            tmp->addWidget(attr.prefix);
            tmp->setFixedSize(16, 16);
            editWidget->addWidget(tmp);
//            editWidget->addWidget(attr.prefix);
        }

        auto *edit = new QLineEdit(this);
        edit->setFont(font);
        edit->setPlaceholderText("...");
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
        editWidget->setStyleSheet(editWidget->getJoinStyles());

        if (0) {
            auto *btn = new QPushButton(this);
            btn->setText("TEXT");
//            btn->setFixedHeight(themeConfig.inputFontSize + themeConfig.paddingBlock * 2);
            btn->setStyleSheet(QString::fromStdString(buttonStyle.str()));
            btn->setFont(font);
            layout->addWidget(btn);
        }
//        layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Minimum));
        this->setLayout(layout);

        LOG_INFO(this->getJoinStyles().toStdString());
//        this->setStyleSheet("padding-left:10px");
//        this->setStyleSheet(this->getJoinStyles());
    }

    Input::Input(const InputAttr &inputAttr, QWidget *parent) : QWidget(parent) {
        this->setAttr(inputAttr);
    }

}

