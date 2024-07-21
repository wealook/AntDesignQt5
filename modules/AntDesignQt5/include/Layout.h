#pragma  once

#include <QWidget>

namespace wl {

    class Layout : public QWidget {

    public:
        explicit Layout(QWidget *parent = nullptr);

        void addWidget(QWidget *widget);

        void initLayout();
        void resizeEvent(QResizeEvent *event) override;

    private:
        std::vector<QWidget *> widgets;
    };

}
