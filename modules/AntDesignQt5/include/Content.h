#pragma once

#include "QWidget"
#include "QScrollArea"

namespace wl {
    class Content : public QScrollArea {
    public:
        explicit Content(QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

        void setContentWidget(QWidget *widget);

    private:
        QWidget *contentWidget = nullptr;
    };

}
