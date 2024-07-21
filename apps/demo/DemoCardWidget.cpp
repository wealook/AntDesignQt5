//
 ///7/12.
//

#include <QPushButton>
#include "DemoCardWidget.h"
#include "Card.h"

DemoCardWidget::DemoCardWidget(QWidget *parent) : DemoContentWidget(parent) {
    this->layoutLeft_->addWidget(new wl::Card());
    this->layoutLeft_->addWidget(new wl::Card());
    this->layoutRight_->addWidget(new wl::Card());
    this->layoutRight_->addWidget(new wl::Card());
}
