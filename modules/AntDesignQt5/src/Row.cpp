//

//

#include <QPushButton>
#include "Row.h"
#include "QLayout"
#include "logger.h"
#include "qevent.h"
#include "ThemeConfig.h"

namespace wl {
    Row::Row(QWidget *parent) : QWidget(parent) {
//        this->setStyleSheet("border: 1px solid green;");
        this->setStyleSheet("border: none;");
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//        this->setMinimumWidth(10);
//        this->setMaximumWidth(16777215);
//        this->setMinimumHeight(10);
        auto *ly = new QVBoxLayout();
        ly->setSpacing(0);
        ly->setMargin(0);
        this->setLayout(ly);
    }

    void Row::resizeEvent(QResizeEvent *event) {
        auto *parent = this->parentWidget();
        if (event->oldSize().width() != event->size().width()) {
            this->flushContent();
        }
        QWidget::resizeEvent(event);
    }

    void Row::addCol(Col *col) {
        this->cols.push_back(col);
        auto *colWidget = new QWidget();
        auto *colLayout = new QHBoxLayout();
        colLayout->setSpacing(0);
        colLayout->setMargin(0);
        colLayout->addWidget(col);
        colWidget->setLayout(colLayout);
        col->setParent(colWidget);
        colWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//        colWidget->setStyleSheet("border: 1px solid orange;");

        this->colWidgets.push_back(colWidget);
    }

    void Row::flushContent() {
//        for (auto it: this->colWidgets) {
//            auto btn = new QPushButton("txt");
//            btn->setFixedHeight(45);
//            btn->setStyleSheet("border:1px solid red");
//            this->layout()->addWidget(btn);
//        }
//        return;
        auto themeConfig = ThemeConfig::Instance();
//        LOG_INFO("start t1")
        {
            auto *rowLayout = this->layout();
            if (rowLayout != nullptr) {
                QLayoutItem *child;
                while ((child = rowLayout->takeAt(0)) != nullptr) {
                    if (child->widget()) {
                        auto hLayout = child->widget()->layout();
                        QLayoutItem *child2;
                        while ((child2 = hLayout->takeAt(0)) != nullptr) {
                            if (child2->widget()) {
                                child2->widget()->setParent(nullptr);
                                if (std::find(this->colWidgets.begin(), this->colWidgets.end(), child2->widget()) == this->colWidgets.end()) {
                                    delete child2->widget();
                                } else {
                                }
                            }
                        }
                    }
                    delete child;
                }
            }
        }

        int gridSum = 0;
        auto *widget = new QWidget(this);
//        widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

//        widget->setMinimumWidth(100);
        auto *ly = new QHBoxLayout(widget);
        ly->setSpacing(0);
        ly->setMargin(0);
        this->layout()->addWidget(widget);
//        LOG_INFO(this->width())
        auto width = this->width();
        auto sizeName = ResponseSize::getResponseSizeName(width);
        for (int index = 0; index < this->cols.size(); index++) {
            auto col = this->cols[index];
            auto colWidget = this->colWidgets[index];
            auto attr = col->getAttr();
            if (gridSum + attr.getSpan(sizeName) + attr.getOffset(sizeName) > 24
                && attr.getSpan(sizeName) + attr.getOffset(sizeName) <= 24) {
                ly->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
                widget = new QWidget(this);
//                widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//                widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                ly = new QHBoxLayout(widget);
                ly->setSpacing(0);
                ly->setMargin(0);
                this->layout()->addWidget(widget);
                gridSum = 0;
//                continue;
            }
            if (attr.getSpan(sizeName) > 0) {
                auto *offsetWidget = new QWidget();
                offsetWidget->setFixedWidth(this->width() * (attr.getOffset(sizeName)) / 24);
                offsetWidget->setStyleSheet(QString::fromStdString("background-color:" + themeConfig.colorInfoBg + ";"));
                offsetWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
                ly->addWidget(offsetWidget);
            }
            colWidget->setFixedWidth(this->width() * (attr.getSpan(sizeName)) / 24);
            ly->addWidget(colWidget);
            gridSum += attr.getSpan(sizeName) + attr.getOffset(sizeName);
            widget->setFixedHeight(100);
        }
        ly->addSpacerItem(new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
//        LOG_INFO("start t2")
    }
}