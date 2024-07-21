//
 ///7/15.
//

#include "Title.h"
#include "QLayout"
#include "QLabel"

namespace wl {

    Title::Title(const QString &text, uint16_t level, QWidget *parent) : QWidget(parent) {
        this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        this->setMinimumWidth(10);
        auto *ly = new QHBoxLayout(this);
        ly->setSpacing(0);
        ly->setMargin(0);
        auto *label = new QLabel(text);
        this->setStyleQss("border", "none");

        if (level == 1) {
            this->setStyleQss("font-size", "38px");
            this->setStyleQss("margin-bottom", "19px");
            this->setFixedHeight(60);
        } else if (level == 2) {
            this->setStyleQss("font-size", "30px");
            this->setStyleQss("margin-top", "36px");
            this->setStyleQss("margin-bottom", "15px");
            this->setFixedHeight(81);
        } else if (level == 3) {
            this->setStyleQss("font-size", "24px");
            this->setStyleQss("margin-top", "28px");
            this->setStyleQss("margin-bottom", "12px");
            this->setFixedHeight(64);
        } else if (level == 4) {
            this->setStyleQss("font-size", "20px");
            this->setStyleQss("margin-top", "24px");
            this->setStyleQss("margin-bottom", "10px");
            this->setFixedHeight(60);
        }

        label->setStyleSheet(this->getJoinStyles());
        ly->addWidget(label);
    }
}