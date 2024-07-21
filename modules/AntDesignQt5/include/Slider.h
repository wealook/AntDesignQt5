#pragma once

#include "QWidget"
#include <QScrollArea>
#include <QListWidget>
namespace wl {

    class Slider : public QWidget {
    Q_OBJECT
    public:
        explicit Slider(QWidget *parent = nullptr);
        void resizeEvent(QResizeEvent *event) override;

        void test();
    };


}


