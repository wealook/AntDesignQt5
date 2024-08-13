#include "Br.h"

namespace wl {


    wl::Br::Br(int height, QWidget *parent) {
        this->setFixedHeight(height);
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
}