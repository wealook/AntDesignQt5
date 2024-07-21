//
 ///7/9.
//

#include "Header.h"
#include "logger.h"

namespace wl {
    Header::Header(QWidget *parent) {
        this->setStyleSheet("border: 1px solid red;");
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        this->setFixedHeight(50);
        this->setMinimumWidth(100);
    }

    void Header::test() {
        LOG_INFO(this << "header test")
    }
}
