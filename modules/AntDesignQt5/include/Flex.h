#pragma  once

#include "HWidget.h"

namespace wl {

    class Flex : public HWidget {

    public:
        explicit Flex(HWidget *parent = nullptr);

        void addWidget(QWidget *wid);

        void insertWidget(int index, QWidget *wid);
    };
}
