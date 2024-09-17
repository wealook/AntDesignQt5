#pragma  once

#include "HWidget.h"
#include "Text.h"
#include "Select.h"
#include "Input.h"
#include "Icon.h"
#include "QPushButton"
#include "ThemeConfig.h"
#include "GeneralAttr.h"
#include "Util.h"
#include "QLayout"

namespace wl {

    class PaginationNumber : public QPushButton {
    Q_OBJECT
    public:
        explicit PaginationNumber(int page, QWidget *parent = nullptr) : QPushButton(parent), page_(page) {
            this->setText(QString::fromStdString(std::to_string(page)));
            this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        }

        void updateAttr() {
            auto &theme = ThemeConfig::Instance();
            aWidget_.setStyleQssFource("border-radius", std::to_string(theme.borderRadiusSM) + "px");
            if (this->checked) {
                aWidget_.setStyleQssFource("border", "1px solid " + theme.colorPrimaryTextHover);
                aWidget_.setStyleQssFource("color", theme.colorPrimaryTextHover);
            } else {
                aWidget_.setStyleQssFource("border", "none");
                aWidget_.setStyleQssFource("color", theme.colorText);
                aWidget_.setStyleQss("hover", "background-color", theme.colorBgSecondary);
            }
            aWidget_.setStyleQss("font-size", "14px");
            aWidget_.setStyleQss("font-weight", "400");
//            aWidget_.setStyleQss("margin-right", "8px");
//            this->setFixedHeight(32);
//            this->setFixedWidth(40);
            this->setStyleSheet(aWidget_.getJoinStyles());
        }

        void paintEvent(QPaintEvent *event) override {
            this->updateAttr();
            QPushButton::paintEvent(event);
        }

        uint32_t getPage() const {
            return page_;
        }

        AWidget aWidget_;
    private:
        bool checked = true;
        uint32_t page_ = 1;
    public:
        bool isChecked1() const {
            return checked;
        }

        void setChecked1(bool b) {
            PaginationNumber::checked = b;
        }
    };

    class PaginationQuickJumper : public HWidget {
    Q_OBJECT
    public:
        explicit PaginationQuickJumper(int type, QWidget *parent = nullptr) : HWidget(parent), type_(type) {
            this->layout()->setAlignment(Qt::AlignCenter);
            this->setContentsMargins(1, 1, 1, 1);
            auto theme = ThemeConfig::Instance();
            if (type_ == -1) {
                icon_ = new Icon("DoubleLeftOutlined", Util::fromCssColor(theme.colorPrimary));
            } else {
                icon_ = new Icon("DoubleRightOutlined", Util::fromCssColor(theme.colorPrimary));
            }
            this->setStyleQssFource("border-radius", "none");
//            this->setStyleQssFource("border", "1px solid red");
            this->setStyleQssFource("border", "none");
//            aWidget_.setStyleQss("border","1px solid red");
//            this->setContentsMargins(1, 1, 1, 1);
//            this->icon_->setFixedSize(18, 18);

            text_ = new Text(u8"\u2022\u2022\u2022");
            text_->setStyleQss("text-align", "center");
            text_->setStyleQss("color", theme.colorText);
            text_->updateAttr();
//            text_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

//            this->icon_->setHidden(true);
            this->addWidget(text_);
//            this->addWidget(icon_);

            this->enterEventCB = [this](QEvent *event) {
                this->removeWidget(this->text_);
                this->addWidget(this->icon_);
            };
            this->leaveEventCB = [this](QEvent *event) {
                this->removeWidget(this->icon_);
                this->addWidget(this->text_);
            };
            this->setStyleSheet(this->getJoinStyles());
        }

        int getType() const {
            return type_;
        }

        void updateAttr() {
            if (this->attrSize == GeneralAttrSize::small) {
                this->text_->setText(u8"\u2022\u2022");
                this->icon_->setFixedSize(14, 14);
            } else {
                this->text_->setText(u8"\u2022\u2022\u2022");
                this->icon_->setFixedSize(20, 20);
            }
        }

    private:
        int type_;
        Icon *icon_ = nullptr;
        Text *text_ = nullptr;
        GeneralAttrSize attrSize = GeneralAttrSize::middle;
    public:
        void setAttrSize(GeneralAttrSize generalAttrSize) {
            PaginationQuickJumper::attrSize = generalAttrSize;
        }
    };

    class Pagination : public HWidget {
    Q_OBJECT
    public:
        explicit Pagination(QWidget *parent = nullptr);

        void updateAttr();

        void calShowPageList(std::vector<int> &result);

        int getPages();

    signals:

        void onChange(uint32_t page, uint32_t pageSize);

    private:

        Text *totalText_ = nullptr;
        Icon *leftIcon_ = nullptr;
        Icon *rightIcon_ = nullptr;
        Icon *leftIcon2_ = nullptr;
        Icon *rightIcon2_ = nullptr;
        HWidget *leftIconWidget_ = nullptr;
        HWidget *rightIconWidget_ = nullptr;
        Select *selectPageSize_ = nullptr;
        Text *jumpText_ = nullptr;
        Input *pageInput_ = nullptr;
        Text *suffixText_ = nullptr;

        HWidget *numbersWidget_ = nullptr;
        std::vector<QWidget *> numbers_;
        std::vector<int> showPageList_;
    private:
        uint32_t attrTotal = 0;
        uint32_t attrPageSize = 20;
        std::vector<uint16_t> attrPageSizeOptions;
        uint32_t attrCurrent = 1;
        bool attrShowSizeChanger = false;
        bool attrShowQuickJumper = false;
        bool attrShowTitle = false;
        bool attrShowTotal = false;
        bool attrSimple = false;
        GeneralAttrSize attrSize = GeneralAttrSize::middle;
    public:
        void setAttrTotal(uint32_t total);

        void setAttrPageSize(uint32_t pageSize);

        void setAttrPageSizeOptions(const std::vector<uint16_t> &pageSizeOptions);

        void setAttrCurrent(int current);

        void setAttrShowSizeChanger(bool showSizeChanger);

        void setAttrShowTitle(bool showTitle);

        void setAttrShowTotal(bool showTotal);

        void setAttrSimple(bool simple);

        void setAttrSize(GeneralAttrSize generalAttrSize);

        void setAttrShowQuickJumper(bool quickJumper);

        uint32_t getAttrPageSize() const;
    };
}

