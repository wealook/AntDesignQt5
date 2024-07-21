#pragma  once

#include "QWidget"
#include "AWidget.h"

namespace wl {

    class Card : public QWidget, public AWidget {


    public:


        explicit Card(QWidget *parent = nullptr);

        void setContent(QWidget *);

        void setContentWidget(QWidget *);

        void resizeEvent(QResizeEvent *event) override;

    private:

        QWidget *extra_ = nullptr;
        QWidget *content_ = nullptr;
        QWidget *contentWidget_ = nullptr;
    };

}



