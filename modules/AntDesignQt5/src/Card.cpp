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
#include "qevent.h"

namespace wl {

    Card::Card(QWidget *parent) : QWidget(parent), AWidget() {
        ThemeConfig themeConfig = ThemeConfig::Instance();
        this->setStyleQss("QWidget", "border-radius", std::to_string(themeConfig.borderRadiusLG) + "px");
        this->setStyleQss("QWidget", "border", "1px solid " + themeConfig.colorBorder);
//        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setMinimumWidth(100);
//        this->setMinimumHeight(300);
        auto ly = new QVBoxLayout(this);
        ly->setSpacing(2);
        ly->setMargin(0);
        this->extra_ = new QWidget(this);
        this->extra_->setFixedHeight(40);
        this->extra_->hide();

        this->content_ = new QWidget(this);
        auto *contentLayout = new QVBoxLayout(content_);
        this->content_->setLayout(contentLayout);
//        this->content_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ly->addWidget(content_);
//        ly->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));

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
        this->contentWidget_->setParent(this->content_);
        this->content_->layout()->addWidget(this->contentWidget_);

    }

    void Card::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
    }
}