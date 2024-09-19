#include <QHBoxLayout>
#include "Divider.h"
#include "QPushButton"
#include "qevent.h"
#include "ThemeConfig.h"

namespace wl {


    Divider::Divider(bool vertical, QWidget *parent) :
            QWidget(parent),
            attrType(vertical ? GeneralAttrTypeDirection::vertical : GeneralAttrTypeDirection::horizontal) {

        if (this->attrType == GeneralAttrTypeDirection::horizontal) {
            childrenWidget_ = new HWidget(this);
            this->childrenWidget_->setFixed();
            this->childrenWidget_->setStyleQss("border", "none");
            this->childrenWidget_->setStyleSheet(this->childrenWidget_->getJoinStyles());
            childrenWidget_->setMaximumHeight(55);
            text_ = new Text("");
            auto themeConfig = ThemeConfig::Instance();

            auto *ly = new QHBoxLayout();
            ly->setMargin(0);
            ly->setSpacing(0);
            this->setLayout(ly);
            left_ = new QWidget(this);
            left_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            left_->setFixedHeight(55);
            left_->setStyleSheet("border: 1px solid " + QString::fromStdString(themeConfig.colorBorder) + ";margin-top:27px;margin-bottom:27px;margin-right:10px;");
//            left_->setStyleSheet("border: 1px solid red  ;margin-top:27px;margin-bottom:27px;margin-right:10px;");
            right_ = new QWidget(this);
            right_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            right_->setFixedHeight(55);
            right_->setStyleSheet("border: 1px solid " + QString::fromStdString(themeConfig.colorBorder) + ";margin-top:27px;margin-bottom:27px;margin-left:10px;");
            ly->addWidget(left_);
            ly->addWidget(this->childrenWidget_);
            ly->addWidget(right_);
        }
        this->updateAttr();
    }

    void Divider::resizeEvent(QResizeEvent *event) {
        auto themeConfig = ThemeConfig::Instance();

        if (this->layout()) {
            auto width = event->size().width();
            auto left = width * 0.1;
            if (this->attrOrientation == DividerAttrOrientation::center) {
                left = width * 0.5;
            } else if (this->attrOrientation == DividerAttrOrientation::right) {
                left = width * (1 - 0.1);
            }
            this->left_->setFixedWidth((int) left);
        }
        QWidget::resizeEvent(event);
    }

    Divider *Divider::createLeft(const QString &text) {
        auto *t = new Divider(text);
        t->setAttrOrientation(wl::DividerAttrOrientation::left);
        t->updateAttr();
        return t;
    }

    Divider::Divider(const QString &text, QWidget *parent) : Divider(false, parent) {
        this->setAttrChildrenText(text);
        this->updateAttr();
    }

    Divider::Divider(const QString &text, DividerAttrOrientation orientation, QWidget *parent) :
            Divider(false, parent) {
        this->setAttrChildrenText(text);
        this->setAttrOrientation(orientation);
        this->updateAttr();
    }

    void Divider::setAttrChildrenText(const QString &childrenText) {
        Divider::attrChildrenText = childrenText;
    }

    void Divider::setAttrChildren(QWidget *children) {
        Divider::attrChildren = children;
    }

    void Divider::setAttrDashed(bool dashed) {
        Divider::attrDashed = dashed;
    }

    void Divider::setAttrOrientation(DividerAttrOrientation orientation) {
        Divider::attrOrientation = orientation;
    }


    void Divider::updateAttr() {
        auto themeConfig = ThemeConfig::Instance();

        this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        if (this->attrType == GeneralAttrTypeDirection::vertical) {
            this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
            this->setFixedWidth(17);
            this->setMinimumHeight(10);
            this->setStyleSheet("border: 1px solid " + QString::fromStdString(themeConfig.colorBorder) + ";margin-left:8px;margin-right:8px;");
            return;
        }
        if (this->attrChildren == nullptr && this->attrChildrenText.isEmpty()) {
            this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            this->childrenWidget_->setVisible(false);
            this->left_->setVisible(false);
            this->right_->setVisible(false);
            this->setFixedHeight(49);
            this->setStyleSheet("border: 1px solid " + QString::fromStdString(themeConfig.colorBorder) + ";margin-top:24px;margin-bottom:24px;");
            return;
        }
        this->setStyleSheet("border: none");
        this->childrenWidget_->setVisible(true);
        this->left_->setVisible(true);
        this->right_->setVisible(true);
        this->text_->setText(this->attrChildrenText);
        if (this->attrChildren != nullptr) {
            this->childrenWidget_->removeWidget(this->text_);
            this->childrenWidget_->insertWidget(1, this->attrChildren);
        } else {
            this->childrenWidget_->removeWidget(this->attrChildren);
            this->childrenWidget_->insertWidget(1, this->text_);
        }


    }

    Divider::Divider(QWidget *children, DividerAttrOrientation orientation, QWidget *parent) :
            Divider(false, parent) {
        this->setAttrChildren(children);
        this->setAttrOrientation(orientation);
        this->updateAttr();
    }


}
