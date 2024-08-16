
#include <QStyleOption>
#include "HWidget.h"
#include "QHBoxLayout"
#include "QMouseEvent"
#include "QPainter"

namespace wl {

    HWidget::HWidget(QWidget *parent, bool spacer) : QWidget(parent) {
        globalHoverAttributes.emplace_back("background-color");
        // border 常用场景中可能会有冲突
//        globalHoverAttributes.emplace_back("border");
        auto *ly = new QHBoxLayout();
        this->setLayout(ly);
        ly->setSpacing(0);
        ly->setMargin(0);
        if (spacer) {
            ly->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        } else {
        }
    }

    void HWidget::addWidget(QWidget *wid) {
        auto *ly = dynamic_cast<QHBoxLayout *>(this->layout());
        ly->insertWidget(ly->count(), wid);
//        ly->insertWidget(ly->count() - 1, wid, 0, Qt::AlignmentFlag::AlignRight);
    }

    void HWidget::enterEvent(QEvent *event) {
        // 覆盖默认的hover样式，原则是:子组件的配置globalHoverAttributes的hover样式应该与父组件保持一致
        if (this->globalHover) {
            if (this->layout() != nullptr) {
                QLayoutItem *child;
                auto count = this->layout()->count();
                for (int index = 0; index < count; index++) {
                    child = this->layout()->itemAt(index);
                    if (child && child->widget()) {
                        auto *hwi = dynamic_cast<HWidget *>(child->widget());
                        if (hwi != nullptr) {
                            for (const auto &it: this->globalHoverAttributes) {
                                if (this->existStyleQss("hover", it)) {
                                    hwi->setStyleQssFource("background-color", this->getStyleQss("hover", it));
                                }
                            }
                            hwi->setStyleSheet(hwi->getJoinStyles());
                        }


                    }
                }
            }
        }

        if (this->enterEventCB) {
            this->enterEventCB(event);
        }
        if (event != nullptr) {
            QWidget::enterEvent(event);
        }
    }

    void HWidget::leaveEvent(QEvent *event) {
        if (this->globalHover) {
            if (this->layout() != nullptr) {
                QLayoutItem *child;
                auto count = this->layout()->count();
                for (int index = 0; index < count; index++) {
                    child = this->layout()->itemAt(index);
                    if (child && child->widget()) {
                        auto *hwi = dynamic_cast<HWidget *>(child->widget());
                        if (hwi != nullptr) {
                            for (const auto &it: this->globalHoverAttributes) {
                                if (this->existStyleQss("!hover", it)) {
                                    hwi->setStyleQssFource("background-color", this->getStyleQss("!hover", it));
                                }
                            }
                            hwi->setStyleSheet(hwi->getJoinStyles());
                        }
                    }
                }
            }
        }
        if (this->leaveEventCB) {
            this->leaveEventCB(event);
        }
        if (event != nullptr) {
            QWidget::leaveEvent(event);
        }
    }

    void HWidget::mousePressEvent(QMouseEvent *event) {
        QWidget::mousePressEvent(event);
        emit clicked();
    }

    void HWidget::mouseReleaseEvent(QMouseEvent *event) {
        QWidget::mouseReleaseEvent(event);
    }

    void HWidget::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        {
//            https://blog.csdn.net/dee53994040/article/details/102178938
            // 修复使用了 Q_OBJECT 后stylesheet无效的问题
            QStyleOption opt;
            opt.init(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

        }

        QWidget::paintEvent(event);
    }

    void HWidget::setFixed() {
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    bool HWidget::isGlobalHover() const {
        return globalHover;
    }

    void HWidget::setGlobalHover(bool globalHoverPa) {
        this->globalHover = globalHoverPa;
    }

}