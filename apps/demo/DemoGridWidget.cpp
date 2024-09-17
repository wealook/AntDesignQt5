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
#include "VWidget.h"
DemoGridWidget::DemoGridWidget(QWidget *parent) : QWidget(parent) {
    auto *ly = new QVBoxLayout();
    ly->setMargin(0);
    ly->setSpacing(0);
    this->setLayout(ly);
    {
        auto *card = new wl::Card();
        ly->addWidget(card);
        auto *wi = new wl::VWidget();
        card->setContentWidget(wi);
        std::random_device rd;
        unsigned int seed = rd();
        std::minstd_rand0 gen(seed);
        {
            auto *row = new wl::Row(this);
            for (int index = 0; index < 50; index++) {
                int randomSpan = gen() % 6 + 2;
                int randomOffset = gen() % 4 + 1;
//                int randomSpan = 6;l
                auto *col = new wl::Col(QString::fromStdString("offset-" + std::to_string(randomOffset) + " COl-" + std::to_string(randomSpan)));
                auto attr = col->getAttr();
                attr.offset = randomOffset;
//                attr.span = wl::ResponseSize(24, 12, 6, 4, 4, 3);
                attr.span = randomSpan;
                col->setAttr(attr);
                row->addCol(col);
            }
            row->flushContent();
            wi->addWidget(row);
        }
    }

}

void DemoGridWidget::resizeEvent(QResizeEvent *event) {
    LOG_INFO(event->size().width() << "," << event->size().height())
    QWidget::resizeEvent(event);
}
