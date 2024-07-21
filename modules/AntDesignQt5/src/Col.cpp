//

//

#include "Col.h"
#include "QLayout"
#include "qevent.h"
#include "QLabel"
#include "QPushButton"

namespace wl {

    Col::Col(QWidget *parent) : QWidget(parent) {
        this->setStyleSheet("border: 1px solid orange;");
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setMinimumHeight(20);
        auto *ly = new QVBoxLayout();
        ly->setMargin(0);
        ly->setSpacing(0);
//        ly->addWidget(new QPushButton("COL"));
        this->setLayout(ly);
    }

    void Col::setContentWidget(QWidget *wid) {
        if (this->contentWidget_) {
            this->contentWidget_->setParent(nullptr);
        }
        this->contentWidget_ = wid;
        auto *rowLayout = this->layout();
        if (rowLayout != nullptr) {
            QLayoutItem *child;
            while ((child = rowLayout->takeAt(0)) != nullptr) {
                if (child->widget()) {
                    child->widget()->setParent(nullptr);
                }
                delete child;
            }
        }
        this->layout()->addWidget(this->contentWidget_);

    }

    void Col::resizeEvent(QResizeEvent *event) {
//        this->contentWidget->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
        QWidget::resizeEvent(event);
    }

    const ColAttr &Col::getAttr() const {
        return attr;
    }

    void Col::setAttr(const ColAttr &colAttr) {
        this->attr = colAttr;
    }

    Col::Col(const QString &txt, QWidget *parent) {
        this->setStyleSheet("border: 1px solid orange;");
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setMinimumHeight(20);
        auto *ly = new QVBoxLayout();
        ly->setMargin(0);
        ly->setSpacing(0);
        auto btn = new QPushButton(txt);
        btn->setFixedHeight(50);
//        btn->setStyleSheet("background-color:green;");
        ly->addWidget(btn);
        this->setLayout(ly);
    }
}