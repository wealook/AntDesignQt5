#include "Pagination.h"

namespace wl {

    Pagination::Pagination(QWidget *parent) : HWidget(parent) {
        this->setFixed();
        this->setStyleQssFource("border", "none");
        this->setContentsMargins(1, 1, 8, 1);
        auto theme = ThemeConfig::Instance();
        this->leftIcon_ = new Icon("LeftOutlined", Util::fromCssColor(theme.colorIcon));
        this->rightIcon_ = new Icon("RightOutlined", Util::fromCssColor(theme.colorIcon));
        this->leftIcon2_ = new Icon("LeftOutlined", Util::fromCssColor(theme.colorIconHover));
        this->rightIcon2_ = new Icon("RightOutlined", Util::fromCssColor(theme.colorIconHover));

        this->leftIconWidget_ = new HWidget(this);
        this->leftIconWidget_->addWidget(this->leftIcon_);
        this->rightIconWidget_ = new HWidget(this);
        this->rightIconWidget_->addWidget(this->rightIcon_);

        this->totalText_ = new Text("Total");
        this->numbersWidget_ = new HWidget(this);
        this->selectPageSize_ = new Select();
        this->jumpText_ = new Text(u8"跳转到");
        this->suffixText_ = new Text(u8"页");

        this->addWidget(this->totalText_);
        this->addWidget(this->leftIconWidget_);
        this->totalText_->setContentsMargins(1, 1, 8, 1);
        this->numbersWidget_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        this->addWidget(this->numbersWidget_);
        this->addWidget(this->rightIconWidget_);
        this->selectPageSize_->setMinimumWidth(120);
        this->addWidget(this->selectPageSize_);
        this->selectPageSize_->setContentsMargins(1, 1, 8, 1);

        this->addWidget(this->jumpText_);
        this->jumpText_->setContentsMargins(1, 1, 8, 1);
        this->pageInput_ = new Input();
        this->pageInput_->setMinimumWidth(100);
        this->pageInput_->setContentsMargins(1, 1, 8, 1);
        this->addWidget(this->pageInput_);
        this->addWidget(this->suffixText_);
        connect(this->leftIconWidget_, &HWidget::clicked, this, [this]() {
            this->setAttrCurrent((int) this->attrCurrent - 1);
            this->updateAttr();
        }, Qt::QueuedConnection);
        connect(this->rightIconWidget_, &HWidget::clicked, this, [this]() {
            this->setAttrCurrent((int) this->attrCurrent + 1);
            this->updateAttr();
        }, Qt::QueuedConnection);
    }

    void Pagination::updateAttr() {

        this->totalText_->setText(QString::fromStdString("Total:" + std::to_string(attrTotal)));
        SelectAttrOptions options;
        for (auto it: this->attrPageSizeOptions) {
            options.emplace_back(std::to_wstring(it) + L"条/页", std::to_wstring(it));
        }
        this->selectPageSize_->setAttrSize(GeneralAttrSize::small);
        this->selectPageSize_->setAttrOptions(options);
        auto sizeHeight = 32;
        auto iconHeight = 12;
        auto margin = 8;
        if (this->attrSize == GeneralAttrSize::small) {
            sizeHeight = 22;
            margin = 0;
        }
        this->leftIcon_->setFixedSize(iconHeight, iconHeight);
        this->leftIcon2_->setFixedSize(iconHeight, iconHeight);
        this->leftIconWidget_->setFixedSize(sizeHeight, sizeHeight);
        this->leftIconWidget_->layout()->setContentsMargins(1, 1, 6, 1);

        this->rightIcon_->setFixedSize(iconHeight, iconHeight);
        this->rightIcon2_->setFixedSize(iconHeight, iconHeight);
        this->rightIconWidget_->setFixedSize(sizeHeight, sizeHeight);
        this->rightIconWidget_->layout()->setContentsMargins(6, 1, 1, 1);

        if (this->attrCurrent == 1) {
            this->leftIconWidget_->replaceWidget(this->leftIcon_, this->leftIcon2_);
        } else {
            this->leftIconWidget_->replaceWidget(this->leftIcon2_, this->leftIcon_);
        }
        if (this->attrCurrent == this->getPages()) {
            this->rightIconWidget_->replaceWidget(this->rightIcon_, this->rightIcon2_);
        } else {
            this->rightIconWidget_->replaceWidget(this->rightIcon2_, this->rightIcon_);
        }
        {
            this->calShowPageList(this->showPageList_);
            for (auto it: this->numbers_) {
                this->numbersWidget_->removeWidget(it, true);
            }
            this->numbers_.clear();
            for (auto it: showPageList_) {
                if (it == -1 || it == -2) {
                    auto *wid = new PaginationQuickJumper(it, this);
                    wid->setAttrSize(this->attrSize);
                    wid->updateAttr();
                    wid->setFixedSize(sizeHeight, sizeHeight);
                    wid->layout()->setContentsMargins(1, 1, 8, 1);
                    connect(wid, &PaginationQuickJumper::clicked, this, [this, wid]() {
                        if (wid->getType() == -1) {
                            if (this->attrCurrent <= 6) {
                                this->setAttrCurrent(1);
                            } else {
                                this->setAttrCurrent((int) this->attrCurrent - 5);
                            }
                            this->updateAttr();
                        } else {
                            this->setAttrCurrent((int) this->attrCurrent + 5);
                            this->updateAttr();
                        }
                    }, Qt::QueuedConnection);
                    this->numbers_.push_back(wid);
                } else {
                    auto *wid = new PaginationNumber(it);
                    wid->aWidget_.setStyleQss("margin-right", std::to_string(margin) + "px");
                    wid->setChecked1(it == this->attrCurrent);
                    wid->setFixedSize(sizeHeight + margin, sizeHeight);
                    wid->updateAttr();
                    connect(wid, &PaginationNumber::clicked, this, [this, wid]() {
                        this->setAttrCurrent(wid->getPage());
                        this->updateAttr();
                    }, Qt::QueuedConnection);
                    this->numbers_.push_back(wid);
                }
            }
            for (auto it: numbers_) {
                this->numbersWidget_->addWidget(it);
            }
        }
        this->selectPageSize_->setVisible(this->attrShowSizeChanger);
        this->totalText_->setVisible(this->attrShowTitle);
        this->jumpText_->setVisible(this->attrShowQuickJumper);
        this->pageInput_->setVisible(this->attrShowQuickJumper);
        this->suffixText_->setVisible(this->attrShowQuickJumper);
    }

    void Pagination::setAttrTotal(uint32_t total) {
        Pagination::attrTotal = total;
    }

    void Pagination::setAttrPageSize(uint32_t pageSize) {
        Pagination::attrPageSize = pageSize;
    }

    void Pagination::setAttrPageSizeOptions(const std::vector<uint16_t> &pageSizeOptions) {
        Pagination::attrPageSizeOptions = pageSizeOptions;
    }

    void Pagination::setAttrCurrent(int current) {
        if (current == this->attrCurrent) {
            return;
        }
        if (current <= 0) {
            this->attrCurrent = 1;
        } else {
            this->attrCurrent = current;
        }
        emit onChange(current, this->attrPageSize);
    }

    void Pagination::setAttrShowSizeChanger(bool showSizeChanger) {
        Pagination::attrShowSizeChanger = showSizeChanger;
    }

    void Pagination::setAttrShowTitle(bool showTitle) {
        Pagination::attrShowTitle = showTitle;
    }

    void Pagination::setAttrShowTotal(bool showTotal) {
        Pagination::attrShowTotal = showTotal;
    }

    void Pagination::setAttrSimple(bool simple) {
        Pagination::attrSimple = simple;
    }

    void Pagination::setAttrSize(GeneralAttrSize generalAttrSize) {
        Pagination::attrSize = generalAttrSize;
    }

    void Pagination::calShowPageList(std::vector<int> &result) {
        auto pages = this->getPages();
        auto currentPage = this->attrCurrent > pages ? pages : this->attrCurrent;
        this->attrCurrent = currentPage;
        result.clear();
        if (pages <= 7) {
            for (int index = 1; index <= pages; index++) {
                result.push_back(index);
            }
        } else {
            result.push_back(1);
            if (currentPage <= 4) {
                for (int index = 2; index <= currentPage; index++) {
                    result.push_back(index);
                }
            } else {
                result.push_back(-1);
                result.push_back(currentPage - 2);
                result.push_back(currentPage - 1);
                result.push_back(currentPage);
            }
            if (currentPage >= pages - 3) {
                for (int index = currentPage + 1; index <= pages; index++) {
                    result.push_back(index);
                }
            } else {
                result.push_back(currentPage + 1);
                result.push_back(currentPage + 2);
                result.push_back(-2);
                result.push_back(pages);
            }
        }


    }

    uint32_t Pagination::getAttrPageSize() const {
        if (attrPageSize <= 0) {
            return 15;
        }
        return attrPageSize;
    }

    void Pagination::setAttrShowQuickJumper(bool quickJumper) {
        Pagination::attrShowQuickJumper = quickJumper;
    }

    int Pagination::getPages() {
        return std::ceil(this->attrTotal / (double) this->attrPageSize);
    }
}