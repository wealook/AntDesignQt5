
#include "HWidget.h"
#include "QHBoxLayout"
#include "QMouseEvent"

namespace wl {

    HWidget::HWidget(QWidget *parent, bool spacer) : QWidget(parent) {
        auto *ly = new QHBoxLayout();
        this->setLayout(ly);
        ly->setSpacing(0);
        ly->setMargin(0);
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        if (spacer) {
            ly->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        } else {
        }
    }

    void HWidget::addWidget(QWidget *wid) {
        auto *ly = dynamic_cast<QHBoxLayout *>(this->layout());
        ly->insertWidget(ly->count() - 1, wid, 0, Qt::AlignmentFlag::AlignRight);
    }

    void HWidget::enterEvent(QEvent *event) {
        if (this->enterEventCB) {
            this->enterEventCB(event);
        }
        QWidget::enterEvent(event);
    }

    void HWidget::leaveEvent(QEvent *event) {
        if (this->leaveEventCB) {
            this->leaveEventCB(event);
        }
        QWidget::leaveEvent(event);
    }

    void HWidget::mousePressEvent(QMouseEvent *event) {
        emit clicked();
    }

    void HWidget::mouseReleaseEvent(QMouseEvent *event) {
    }

}