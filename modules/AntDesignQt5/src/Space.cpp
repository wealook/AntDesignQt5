
#include "Space.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QSpacerItem"

namespace wl {

    Space::Space(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f) {

    }

    const SpaceAttr &Space::getAttr() const {
        return attr;
    }

    void Space::setAttr(const SpaceAttr &spaceAttr) {
        this->attr = spaceAttr;

        QLayout *layout;
        QSpacerItem *spacerItem;
        if (this->attr.direction == SpaceAttrDirection::horizontal) {
            layout = new QHBoxLayout(this);
            spacerItem = new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Minimum);
        } else {
            layout = new QVBoxLayout(this);
            spacerItem = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Maximum);
        }

        auto spaceSize = 10;
        if (std::holds_alternative<GeneralAttrSize>(attr.size)) {
            auto size = std::get<GeneralAttrSize>(attr.size);
            if (size == GeneralAttrSize::small) {
                spaceSize = 6;
            } else if (size == GeneralAttrSize::middle) {
                spaceSize = 10;
            } else if (size == GeneralAttrSize::large) {
                spaceSize = 14;
            }
        }
        if (std::holds_alternative<uint16_t>(attr.size)) {
            spaceSize = std::get<uint16_t>(attr.size);
        }
        for (auto &it: this->widgets) {
            auto item = dynamic_cast<AWidget *>(it);
            item->setStyleQss("margin-left", std::to_string(spaceSize) + "px");
            item->setStyleQss("hover", "margin-left", std::to_string(spaceSize) + "px");
//            it->setStyleQss("!hover:{margin-left:10px;}");
            it->setStyleSheet(item->getJoinStyles());
            layout->addWidget(it);
        }
        layout->addItem(spacerItem);
        this->setLayout(layout);
    }

    void Space::addItem(QWidget *wid) {
        this->widgets.push_back(wid);
    }

    void Space::clearItems() {

    }

}


