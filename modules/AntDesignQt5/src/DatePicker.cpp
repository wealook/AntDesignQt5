
#include <QSpacerItem>
#include "DatePicker.h"
#include "ThemeConfig.h"
#include "Util.h"
#include "Text.h"
#include "Row.h"
#include "Col.h"

namespace wl {
    DatePicker::DatePicker(QWidget *parent) : HWidget(parent) {

    }

    DateSelectPanelHeader::DateSelectPanelHeader(QWidget *parent) : HWidget(parent) {
//        this->setFixed();
        this->setContentsMargins(0, 0, 0, 1);
        auto themeConfig = ThemeConfig::Instance();

        this->iconLeft_ = new Icon("LeftOutlined", Util::fromCssColor(themeConfig.colorDisabledBorder));
        this->iconLeft_->setFixedSize(24, 24);
        this->iconDoubleLeft_ = new Icon("DoubleLeftOutlined", Util::fromCssColor(themeConfig.colorDisabledBorder));
        this->iconDoubleLeft_->setFixedSize(24, 24);

        this->iconRight_ = new Icon("RightOutlined", Util::fromCssColor(themeConfig.colorDisabledBorder));
        this->iconRight_->setFixedSize(24, 24);

        this->iconDoubleRight_ = new Icon("DoubleRightOutlined", Util::fromCssColor(themeConfig.colorDisabledBorder));
        this->iconDoubleRight_->setFixedSize(24, 24);

        this->addWidget(iconDoubleLeft_);
        this->addWidget(iconLeft_);
        this->addWidget(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        TextAttr textAttr;
        textAttr.fontSize = 14;
        text_ = new Text("2024");
        text_->setAttr(textAttr);
        this->addWidget(text_);
        this->addWidget(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));

        this->addWidget(iconRight_);
        this->addWidget(iconDoubleRight_);

        this->setStyleQss("border-radius", "0px");
        this->setStyleQss("border-bottom", "1px solid " + themeConfig.colorBorder);
        this->setFixedHeight(41);
        this->setStyleSheet(this->getJoinStyles());
    }

    DateSelectPanelContent::DateSelectPanelContent(QWidget *parent) : HWidget(parent) {

        auto *row = new Row();

        for (int index = 0; index < 50; index++) {
            auto *col = new Col();
            auto *text = new Text("aaa");
            col->setContentWidget(text);
            auto attr = col->getAttr();
            attr.offset = 0;
            attr.span = 5;
            col->setAttr(attr);
            row->addCol(col);
        }
        row->flushContent();

        this->addWidget(row);
    }

    void DateSelectPanelContent::updateAttr() {

    }

    DateSelectPanel::DateSelectPanel(QWidget *parent) : VWidget(parent) {
        this->header_ = new DateSelectPanelHeader(this);
        this->content_ = new DateSelectPanelContent(this);
        this->addWidget(header_);
        this->addWidget(content_);
    }


}