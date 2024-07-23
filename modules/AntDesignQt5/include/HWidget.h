#pragma  once

#include "QWidget"

namespace wl {

    class HWidget : public QWidget {

    public:
        HWidget(QWidget *parent = nullptr);

        void addWidget(QWidget *wid);
    };
}


