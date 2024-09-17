
#include "Flex.h"
#include "Flowlayout.h"
#include "HWidget.h"

namespace wl {

    Flex::Flex(HWidget *parent) : HWidget(parent) {
        this->globalHover = false;
        {
            auto *old = this->layout();
            delete old;
        }
        auto *layout = new FlowLayout();
        this->setLayout(layout);
        layout->setSpacing(0);
        layout->setMargin(1);
//        this->setStyleSheet("border:1px solid blue;");
    }

    void Flex::addWidget(QWidget *wid) {
        auto *ly = dynamic_cast<FlowLayout *>(this->layout());
        ly->addWidget(wid);
    }

    void Flex::insertWidget(int index, QWidget *wid) {
        auto *ly = dynamic_cast<FlowLayout *>(this->layout());
        LOG_INFO("index:" << index)
        ly->insertWidget(index, wid);
    }

}