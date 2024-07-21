
#include "Layout.h"
#include "Slider.h"
#include "QLayout"
#include "qevent.h"
#include "logger.h"
#include "QPushButton"
#include "Header.h"
#include "Content.h"

namespace wl {

    Layout::Layout(QWidget *parent) : QWidget(parent) {
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setMinimumHeight(100);
        this->setMinimumWidth(100);
//        this->setStyleSheet(":!hover{border: 1px solid blue;}");
    }

    void Layout::addWidget(QWidget *widget) {
        this->widgets.push_back(widget);
    }

    void Layout::initLayout() {
        auto *oldLayout = this->layout();
        if (oldLayout != nullptr) {
            QLayoutItem *child;
            while ((child = oldLayout->takeAt(0)) != nullptr) {
                if (child->widget()) {
                    child->widget()->setParent(nullptr);//setParent(nullptr),防止删除之后界面不消失
                }
                delete child;
            }
            oldLayout->setParent(nullptr);
            this->setLayout(nullptr);
        }

        bool hasSlider = false;
        bool hasContent = false;
        bool hasLayout = false;

        for (auto it: this->widgets) {
            auto *slider = dynamic_cast<Slider *>(it);
            if (slider != nullptr) {
                hasSlider = true;
                continue;
            }
            auto *content = dynamic_cast<Content *>(it);
            if (content != nullptr) {
                hasContent = true;
                continue;
            }
            auto *layout = dynamic_cast<Layout *>(it);
            if (layout != nullptr) {
                hasLayout = true;
                continue;
            }
        }
//        LOG_INFO(hasSlider)
        QLayout *layout1;
        QSpacerItem *spacerItem;
        if (hasSlider) {
            layout1 = new QHBoxLayout(this);
            spacerItem = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
        } else {
            layout1 = new QVBoxLayout(this);
            spacerItem = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
        }
        this->setLayout(layout1);
        layout1->setMargin(0);
        layout1->setSpacing(0);
        for (auto it: this->widgets) {
            it->setParent(this);
            layout1->addWidget(it);
        }
//        layout1->addWidget(new QPushButton("hahhaha"));
        if (!hasContent && !hasLayout) {
            layout1->addItem(spacerItem);
        }
    }

    void Layout::resizeEvent(QResizeEvent *event) {
//        LOG_INFO("aa")
        for (auto it: this->widgets) {
//            it->resize(event->size());
        }
        QWidget::resizeEvent(event);
//        this->initLayout();
    }
}