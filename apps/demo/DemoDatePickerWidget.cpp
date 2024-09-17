
#include "DemoDatePickerWidget.h"
#include "DatePicker.h"
#include "VWidget.h"
#include "Card.h"

DemoDatePickerWidget::DemoDatePickerWidget(QWidget *parent) : DemoContentWidget(parent) {

    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);
        wi->addWidget(new wl::DateSelectPanel());
    }
}
