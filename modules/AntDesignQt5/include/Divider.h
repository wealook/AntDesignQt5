#pragma  once

#include "QWidget"
#include "DividerAttr.h"

namespace wl {

    class Divider : public QWidget {

    public:
        static Divider *createLeft(const QString &text);

        explicit Divider(const DividerAttr &attr, QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

    private:
        DividerAttr attr_;
    };


}


