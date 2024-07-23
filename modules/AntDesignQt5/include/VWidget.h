#pragma  once

#include "QWidget"

namespace wl {
    class VWidget : public QWidget {
    public:
        VWidget(QWidget *parent = nullptr);

        void addWidget(QWidget *wid);
    };
}
