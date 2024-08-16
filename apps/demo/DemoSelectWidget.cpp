#include "DemoSelectWidget.h"
#include "Select.h"
#include "VWidget.h"
#include "Card.h"
#include "Divider.h"
#include "Text.h"

DemoSelectWidget::DemoSelectWidget(QWidget *parent) : DemoContentWidget(parent) {

//    this->setStyleSheet("background-color:red;");

    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
//        wi->setMaximumWidth(400);
        card->setContentWidget(wi);
        this->layoutRight_->addWidget(card);

        auto *pSelect = new wl::Select(this);
        auto attrSelect = pSelect->getAttr();
        attrSelect.fixedWidth = 150;
        attrSelect.selectHeight = 200;

        attrSelect.options.clear();
        for (int index = 0; index <= 10; index++) {
            attrSelect.options.emplace_back(
                    QString("item" + QString::fromStdString(std::to_string(index))).toStdWString(),
                    QString("item" + QString::fromStdString(std::to_string(index))).toStdWString()
            );
        }
        pSelect->setAttr(attrSelect);
        wi->addWidget(pSelect);
        wi->addWidget(wl::Divider::createLeft("基本使用"));
        wi->addWidget(new wl::Text("基本使用。"));

    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
//        wi->setMaximumWidth(400);
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);

        auto *pSelect = new wl::Select(this);
        auto attrSelect = pSelect->getAttr();
        attrSelect.fixedWidth = 150;
        attrSelect.selectHeight = 200;

        attrSelect.options.clear();
        for (int index = 0; index <= 10; index++) {
            attrSelect.options.emplace_back(
                    QString("item" + QString::fromStdString(std::to_string(index))).toStdWString(),
                    QString("item" + QString::fromStdString(std::to_string(index))).toStdWString()
            );
        }
        pSelect->setAttr(attrSelect);
        wi->addWidget(pSelect);
    }
}
