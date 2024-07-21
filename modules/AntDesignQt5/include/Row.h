#pragma  once

#include "QWidget"
#include "Col.h"
#include "vector"

namespace wl {
    class Row : public QWidget {
    public:
        explicit Row(QWidget *parent = nullptr);

        void addCol(Col *col);

        void resizeEvent(QResizeEvent *event) override;

        void flushContent();

    private:
        std::vector<Col *> cols;
        std::vector<QWidget *> colWidgets;

    };
}


