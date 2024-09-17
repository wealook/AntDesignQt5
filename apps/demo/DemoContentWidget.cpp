//
 ///7/10.
//

#include "DemoContentWidget.h"
#include "QLayout"
#include "QSpacerItem"
#include <QScrollBar>
#include "qevent.h"
#include "logger.h"

//DemoContentWidget::DemoContentWidget(QWidget *parent) : QScrollArea(parent) {
DemoContentWidget::DemoContentWidget(QWidget *parent) : QWidget(parent) {
//    this->verticalScrollBar()->setStyleSheet(R"(
//            QScrollBar {
//                    width: 8px;
//                    background-color: #f0f0f0;
//                    border: none;
//            }
//            QScrollBar::handle {
//                    background-color: #c8c8c8;
//                    border-radius: 4px;
//            }
//            QScrollBar::handle:hover {
//                    background-color: #c8c8c8;
//                    color:rgba(0,0,0,0.5);
//                    height:50%;
//            }
//            QScrollBar::corner {
//                    background: transparent;
//            }
//        )"
//    );


    // 顶部区域，暂时空着
    auto *widget1 = new QWidget();
    widget1->setFixedHeight(0);
    // 主体区域，两列
    auto *widget2 = new QWidget();

    auto *layout2 = new QHBoxLayout();


    widget2->setLayout(layout2);
    widget2->setStyleSheet("border:none;");

//    widget1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
//    widget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    {
        auto *widget21 = new QWidget();
        auto *widget22 = new QWidget();
        widget21->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        widget22->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);


        layoutLeft_ = new QVBoxLayout();
        layoutRight_ = new QVBoxLayout();

        layoutLeft_->setAlignment(Qt::AlignTop);
        layoutRight_->setAlignment(Qt::AlignTop);

        widget21->setLayout(layoutLeft_);
        widget22->setLayout(layoutRight_);

        layout2->addWidget(widget21);
        layout2->addWidget(widget22);



//        layoutLeft_->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));
//        layoutRight_->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));

    }
//    QWidget *widget = new QWidget();

    auto *layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->addWidget(widget1);
    layout->addWidget(widget2);
    layout->setAlignment(Qt::AlignTop);

//    layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));
//    widget->setStyleSheet("border:1px solid green ;");
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    this->setWidget(widget);
//    this->setStyleSheet("border:1px solid blue ;");

}

void DemoContentWidget::resizeEvent(QResizeEvent *event) {
//    LOG_INFO(event->size().width() << "," << event->size().height())
    QWidget::resizeEvent(event);
}

DemoContentWidget::~DemoContentWidget() = default;
