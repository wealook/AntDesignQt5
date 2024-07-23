#pragma  once

#include "QWidget"
#include "TextAttr.h"
#include "QLabel"

namespace wl {

    class Text : public QWidget {
    public:
        explicit Text(const QString &text, QWidget *parent = nullptr);

        explicit Text(const QString &text, const TextAttr &textAttr, QWidget *parent = nullptr);

        void setAttr(const TextAttr &textAttr);

    private:
        QLabel *label_;
        TextAttr attr_;
    };

}



