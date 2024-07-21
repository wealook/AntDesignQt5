#pragma  once

#include "QWidget"
#include "AWidget.h"

namespace wl {
    class Title : public QWidget, public AWidget {

    public:
        explicit Title(const QString &text, uint16_t level = 1, QWidget *parent = nullptr);
    };
}



