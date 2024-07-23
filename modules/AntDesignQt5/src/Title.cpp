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
        this->setStyleQss("color", "rgba(0, 0, 0, 0.88)");
        this->setStyleQss("font-weight", "600");
        this->setStyleQss("font-family", "Segoe UI");

        if (level == 1) {
            this->setStyleQss("height", "46px");
            this->setStyleQss("font-size", "38px");
            this->setStyleQss("margin-bottom", "19px");
//            this->setFixedHeight(65);
        } else if (level == 2) {
            this->setStyleQss("height", "38px");

            this->setStyleQss("font-size", "30px");
            this->setStyleQss("padding-top", "36px");
            this->setStyleQss("padding-bottom", "15px");
        } else if (level == 3) {
            this->setStyleQss("height", "32px");
            this->setStyleQss("font-size", "24px");
            this->setStyleQss("margin-top", "28px");
            this->setStyleQss("margin-bottom", "12px");
        } else if (level == 4) {
            this->setStyleQss("height", "28px");
            this->setStyleQss("font-size", "20px");
            this->setStyleQss("margin-top", "24px");
            this->setStyleQss("margin-bottom", "10px");
        } else if (level == 5) {
            this->setStyleQss("height", "24px");
            this->setStyleQss("font-size", "16px");
            this->setStyleQss("margin-top", "24px");
            this->setStyleQss("margin-bottom", "10px");
        }

        label->setStyleSheet(this->getJoinStyles());
        ly->addWidget(label);
    }
}