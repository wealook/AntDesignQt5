//
 ///7/15.
//

#include "Text.h"
#include "QLayout"
#include "QLabel"

namespace wl {

    Text::Text(const QString& text, QWidget *parent) {
        this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        this->setMinimumWidth(10);
        auto *ly = new QHBoxLayout(this);
        ly->setSpacing(0);
        ly->setMargin(0);
        auto *label = new QLabel(text);
        ly->addWidget(label);
    }
}