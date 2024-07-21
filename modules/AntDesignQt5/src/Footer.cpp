//
 ///7/9.
//

#include "Footer.h"


namespace wl {
    Footer::Footer(QWidget *parent) {
        this->setStyleSheet("border: 1px solid red;");
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        this->setFixedHeight(50);
        this->setMinimumWidth(100);
    }
}