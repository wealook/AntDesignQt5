//
 ///7/9.
//

#include "Slider.h"
#include "logger.h"
#include "QScrollBar"
#include "qevent.h"

namespace wl {
    Slider::Slider(QWidget *parent) : QWidget(parent) {
//        this->setStyleSheet("border: 1px solid blue;");
        this->setStyleSheet("border: none;");

        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        this->setMinimumHeight(200);
        this->setMaximumWidth(250);
        this->setMinimumWidth(100);
    }

    void Slider::test() {

        LOG_INFO(this << " test")
    }

    void Slider::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
    }
}
