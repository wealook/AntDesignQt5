#pragma  once

#include "QWidget"
#include "functional"
#include "AWidget.h"

namespace wl {
/**
 *  自带水平布局的widget
 */
    class HWidget : public QWidget, public AWidget {

    public:
        explicit HWidget(QWidget *parent = nullptr);

        void addWidget(QWidget *wid);

        void enterEvent(QEvent *event) override;

        void leaveEvent(QEvent *event) override;


        std::function<void(QEvent *event)> enterEventCB = nullptr;
        std::function<void(QEvent *event)> leaveEventCB = nullptr;

    };
}


