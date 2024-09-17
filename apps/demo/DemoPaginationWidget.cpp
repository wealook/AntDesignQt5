
#include "DemoPaginationWidget.h"
#include "Pagination.h"
#include "VWidget.h"
#include "Card.h"
#include "Br.h"
#include "Divider.h"

DemoPaginationWidget::DemoPaginationWidget(QWidget *parent) : DemoContentWidget(parent) {

    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);
        auto *pPagination = new wl::Pagination();
        pPagination->setAttrPageSizeOptions({10, 15, 20, 30, 50, 100});
        pPagination->setAttrTotal(99999);
        pPagination->setAttrPageSize(20);
        pPagination->setAttrCurrent(11);
        pPagination->updateAttr();
        wi->addWidget(pPagination);
        wi->addWidget(new wl::Br(50));
        wi->addWidget(wl::Divider::createLeft("基本使用"));
        wi->addWidget(new wl::Text("基本使用。"));
    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);
        auto *pPagination = new wl::Pagination();
        pPagination->setAttrPageSizeOptions({10, 15, 20, 30, 50, 100});
        pPagination->setAttrSimple(true);
        pPagination->setAttrTotal(99999);
        pPagination->setAttrPageSize(20);
        pPagination->setAttrCurrent(11);
        pPagination->updateAttr();
        wi->addWidget(pPagination);
        wi->addWidget(new wl::Br(50));
        wi->addWidget(wl::Divider::createLeft("简介"));
        wi->addWidget(new wl::Text("简单的翻页"));
    }
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);

        auto *pPagination = new wl::Pagination();
        pPagination->setAttrPageSizeOptions({10, 15, 20, 30, 50, 100});
        pPagination->setAttrSize(wl::GeneralAttrSize::small);
        pPagination->setAttrTotal(999);
        pPagination->setAttrCurrent(1);
        pPagination->updateAttr();
        wi->addWidget(pPagination);
    }
}
