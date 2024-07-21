#pragma  once

#include "QWidget"

namespace wl {

    class Text : public QWidget {
    public:
        explicit Text(const QString& text, QWidget *parent = nullptr);
    };

}



