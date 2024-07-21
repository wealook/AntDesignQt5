//
 ///7/9.
//

#include "Card.h"
#include "ThemeConfig.h"
#include "QLayout"
#include "ThemeConfig.h"
#include "QPushButton"
#include "Icon.h"
#include "Title.h"
#include "Text.h"

namespace wl {

    Card::Card(QWidget *parent) : QWidget(parent) {
        ThemeConfig themeConfig = ThemeConfig::Instance();
        this->setStyleQss("border", "1px solid " + themeConfig.colorBorder);
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setMinimumWidth(100);
//        this->setMinimumHeight(600);
        auto ly = new QVBoxLayout(this);
        ly->setSpacing(2);
        ly->setMargin(0);
        this->extra_ = new QWidget(this);
        this->extra_->setFixedHeight(40);
        this->extra_->hide();

        this->content_ = new QWidget(this);
        this->content_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        auto *contentLayout = new QVBoxLayout(content_);
//
//        contentLayout->setMargin(10);
//        contentLayout->setSpacing(0);
//
//        contentLayout->addWidget(new QPushButton("aaaaaaa"));
//        contentLayout->addWidget(new QPushButton("aaaaaaa"));
//        contentLayout->addWidget(new Title("测试 h1", 1, this));
//        contentLayout->addWidget(new Title("测试 h2", 2, this));
//        contentLayout->addWidget(new Title("测试 h3", 3, this));
//        contentLayout->addWidget(new Title("测试 h4", 4, this));
        ly->addWidget(extra_);
        ly->addWidget(content_);
        this->setStyleSheet(this->getJoinStyles());
    }

    void Card::setContent(QWidget *content) {

    }

    void Card::setContentWidget(QWidget *widget) {
        if (this->contentWidget_) {
            this->contentWidget_->setParent(nullptr);
        }
        auto *rowLayout = this->content_->layout();
        if (rowLayout != nullptr) {
            QLayoutItem *child;
            while ((child = rowLayout->takeAt(0)) != nullptr) {
                if (child->widget()) {
                    child->widget()->setParent(nullptr);
                }
                delete child;
            }
        }
        this->contentWidget_ = widget;
//        this->contentWidget_->setParent(this->content_);
        this->content_->layout()->addWidget(this->contentWidget_);

    }

    void Card::resizeEvent(QResizeEvent *event) {
//        LOG_INFO(this->content_->geometry().size().width())
//        LOG_INFO(this->content_->geometry().size().height())
        if (this->contentWidget_) {
            this->contentWidget_->setGeometry(QRect(0, 0, this->content_->width(), this->content_->height()));
        }
        QWidget::resizeEvent(event);
    }
}