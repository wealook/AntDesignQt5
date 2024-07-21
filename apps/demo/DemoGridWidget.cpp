//
 ///7/15.
//

#include "DemoGridWidget.h"
#include "Row.h"
#include "Col.h"
#include "QLayout"
#include "logger.h"
#include "qevent.h"
#include "random"
#include "Card.h"

DemoGridWidget::DemoGridWidget(QWidget *parent) : QWidget(parent) {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumHeight(10);

    auto *ly = new QVBoxLayout();
    ly->setMargin(0);
    ly->setSpacing(0);
    this->setLayout(ly);
    {

        auto *card = new wl::Card();
        auto *widget = new QWidget();
        auto *layout = new QVBoxLayout(widget);
        std::random_device rd;
        unsigned int seed = rd();
        std::minstd_rand0 gen(seed);
        {
            auto *row = new wl::Row(this);
            for (int index = 0; index < 10; index++) {
                int randomSpan = gen() % 6 + 2;
                int randomOffset = gen() % 4 + 1;
//                int randomSpan = 6;
                auto *col = new wl::Col(QString::fromStdString("offset-" + std::to_string(randomOffset) + " COl-" + std::to_string(randomSpan)));
                auto attr = col->getAttr();
                attr.offset = randomOffset;
//                attr.span = wl::ResponseSize(24, 12, 6, 4, 4, 3);
                attr.span = randomSpan;
                col->setAttr(attr);
                row->addCol(col);
            }
            row->flushContent();
            layout->addWidget(row);
        }
        card->setContentWidget(widget);
        ly->addWidget(card);
        ly->setStretch(0, 1);
    }

}

void DemoGridWidget::resizeEvent(QResizeEvent *event) {
    LOG_INFO(event->size().width() << "," << event->size().height())
    QWidget::resizeEvent(event);
}
