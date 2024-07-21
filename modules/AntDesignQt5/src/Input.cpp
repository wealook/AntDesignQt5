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

namespace wl {

    Input::Input(QWidget *parent) {

    }

    const InputAttr &Input::getAttr() const {
        return attr;
    }

    void Input::setAttr(const InputAttr &inputAttr) {
        auto themeConfig = InputConfig::Instance();
        LOG_INFO("---------------------------------------")
        this->attr = inputAttr;

        std::stringstream labelStyle;
        std::stringstream editStyle;
        std::stringstream buttonStyle;
        if (attr.status == InputAttrStatus::none) {
            labelStyle << ":!hover{ border-style:solid ;border-color:  " + themeConfig.colorBorder + " ;border-width: 1px 0px 1px 1px ; }";
            labelStyle << ":hover{ border-style:solid ;border-color:  " + themeConfig.colorBorder + " ;border-width: 1px 0px 1px 1px ; }";


            editStyle << ":!hover{border:1px solid " + themeConfig.colorBorder + ";}";
            editStyle << ":hover{border:1px solid  " + themeConfig.hoverBorderColor + ";}";
            editStyle << ":focus{border:1px solid  " + themeConfig.activeBorderColor + ";}";

            buttonStyle << ":!hover{ border-style:none ;background-color:  " + themeConfig.colorPrimary + " ;color:white; padding-left:5px;padding-right:5px;}";
            buttonStyle << ":hover{ border-style:none ;background-color:  " + themeConfig.colorPrimaryHover + " ; color:white;padding-left:5px;padding-right:5px;}";
        } else if (attr.status == InputAttrStatus::warning) {

        } else if (attr.status == InputAttrStatus::error) {

        }

        QLayout *layout = new QHBoxLayout(this);
        QSpacerItem *spacerItem = new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Minimum);
        layout->setMargin(0);
        layout->setSpacing(0);
        QFont font;
        font.setPixelSize(themeConfig.inputFontSize);
        if (!attr.textBefore.empty()) {
            auto *label = new QLabel(this);
            label->setText(QString::fromStdWString(attr.textBefore));
//            label->setMargin(0);
//            LOG_INFO(labelStyle.str())
            label->setStyleSheet(QString::fromStdString(labelStyle.str()));

            label->setFont(font);
            label->setFixedHeight(themeConfig.inputFontSize + themeConfig.paddingBlock * 2);
            layout->addWidget(label);
        }

        auto *edit = new QLineEdit(this);
        edit->setFont(font);
        edit->setFixedHeight(themeConfig.inputFontSize + themeConfig.paddingBlock * 2);
        edit->setPlaceholderText("asdadas");
        edit->setStyleSheet(QString::fromStdString(editStyle.str()));
        layout->addWidget(edit);
        {
            auto *btn = new QPushButton(this);
            btn->setText("TEXT");
            btn->setFixedHeight(themeConfig.inputFontSize + themeConfig.paddingBlock * 2);
            btn->setStyleSheet(QString::fromStdString(buttonStyle.str()));
            btn->setFont(font);
            layout->addWidget(btn);
        }
        layout->addItem(spacerItem);
        this->setLayout(layout);
//        this->setStyleSheet(QString::fromStdString(buttonStyle.str()));
    }

}

