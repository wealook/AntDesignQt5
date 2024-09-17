#include <QHBoxLayout>
#include "Divider.h"
#include "QPushButton"
#include "Text.h"
#include "qevent.h"
#include "ThemeConfig.h"

namespace wl {


    Divider::Divider(const DividerAttr &attr, QWidget *parent) : QWidget(parent), attr_(attr) {
        this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        auto themeConfig = ThemeConfig::Instance();
        if (attr.type == GeneralAttrTypeDirection::vertical) {
            this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
            this->setFixedWidth(17);
            this->setMinimumHeight(10);
            this->setStyleSheet("border: 1px solid " + QString::fromStdString(themeConfig.colorBorder) + ";margin-left:8px;margin-right:8px;");
            return;
        }
        if (attr.children == nullptr && attr.childrenText.isEmpty()) {
            this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            this->setFixedHeight(49);
            this->setStyleSheet("border: 1px solid " + QString::fromStdString(themeConfig.colorBorder) + ";margin-top:24px;margin-bottom:24px;");
            return;
        }

        auto *wid = attr.children;
        if (wid == nullptr) {
            wid = new Text(attr.childrenText);
        }
        auto *ly = new QHBoxLayout();
        ly->setMargin(0);
        ly->setSpacing(0);
        this->setLayout(ly);

        auto *left = new QWidget(this);
        left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        left->setFixedHeight(55);
        left->setStyleSheet("border: 1px solid " + QString::fromStdString(themeConfig.colorBorder) + ";margin-top:27px;margin-bottom:27px;margin-right:10px;");
        auto *right = new QWidget(this);
        right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        right->setFixedHeight(55);
        right->setStyleSheet("border: 1px solid " + QString::fromStdString(themeConfig.colorBorder) + ";margin-top:27px;margin-bottom:27px;margin-left:10px;");
        ly->addWidget(left);
        ly->addWidget(wid);
        ly->addWidget(right);
    }

    void Divider::resizeEvent(QResizeEvent *event) {
        auto themeConfig = ThemeConfig::Instance();

        if (this->layout()) {
            auto width = event->size().width();
            auto left = width * 0.1;
            if (attr_.orientation == DividerAttrOrientation::center) {
                left = width * 0.5;
            } else if (attr_.orientation == DividerAttrOrientation::right) {
                left = width * (1 - 0.1);
            }
            this->layout()->itemAt(0)->widget()->setFixedWidth(left);
        }
        QWidget::resizeEvent(event);
    }

    Divider *Divider::createLeft(const QString &text) {
        auto diverAttr = wl::DividerAttr(text);
        diverAttr.orientation = wl::DividerAttrOrientation::left;
        return new Divider(diverAttr);
    }

}
