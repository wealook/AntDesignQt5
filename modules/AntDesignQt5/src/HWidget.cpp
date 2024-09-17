
#include <QStyleOption>
#include "HWidget.h"
#include "QHBoxLayout"
#include "QMouseEvent"
#include "QPainter"
#include "qevent.h"
#include "ThemeConfig.h"

namespace wl {

    HWidget::HWidget(QWidget *parent, bool spacer) : QWidget(parent), AWidget() {
        auto theme = ThemeConfig::Instance();
        this->setStyleQss("font-family", theme.fontFamily);
        globalHoverAttributes.emplace_back("background-color");
        // border 常用场景中可能会有冲突
//        globalHoverAttributes.emplace_back("border");
        auto *ly = new QHBoxLayout();
        this->setLayout(ly);
        ly->setSpacing(0);
        ly->setMargin(0);
        if (spacer) {
            ly->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        } else {
        }
    }

    HWidget::HWidget(bool vertical, QWidget *parent) : QWidget(parent), vertical(vertical) {
        auto theme = ThemeConfig::Instance();
        this->setStyleQss("font-family", theme.fontFamily);
        globalHoverAttributes.emplace_back("background-color");
        auto *ly = new QVBoxLayout();
        this->setLayout(ly);
        ly->setSpacing(0);
        ly->setMargin(0);
    }

    void HWidget::addWidget(QWidget *wid) {
        wid->setParent(this);
        if (this->vertical) {
            auto *ly = dynamic_cast<QVBoxLayout *>(this->layout());
            ly->insertWidget(ly->count(), wid);
        } else {
            auto *ly = dynamic_cast<QHBoxLayout *>(this->layout());
            ly->insertWidget(ly->count(), wid);
        }
//        ly->insertWidget(ly->count() - 1, wid, 0, Qt::AlignmentFlag::AlignRight);
    }

    void HWidget::insertWidget(int index, QWidget *wid) {
        wid->setParent(this);
        if (this->vertical) {
            auto *ly = dynamic_cast<QVBoxLayout *>(this->layout());
            ly->insertWidget(index, wid);
        } else {
            auto *ly = dynamic_cast<QHBoxLayout *>(this->layout());
            ly->insertWidget(index, wid);
        }
//        ly->insertWidget(ly->count() - 1, wid, 0, Qt::AlignmentFlag::AlignRight);
    }

    void HWidget::enterEvent(QEvent *event) {

        // 覆盖默认的hover样式，原则是:子组件的配置globalHoverAttributes的hover样式应该与父组件保持一致
        if (this->globalHover) {
            if (this->layout() != nullptr) {
                QLayoutItem *child;
                auto count = this->layout()->count();
                for (int index = 0; index < count; index++) {
                    child = this->layout()->itemAt(index);
                    if (child && child->widget()) {
                        auto *hwi = dynamic_cast<HWidget *>(child->widget());
                        if (hwi != nullptr) {
                            for (const auto &it: this->globalHoverAttributes) {
                                if (this->existStyleQss("hover", it)) {
                                    hwi->setStyleQssFource("background-color", this->getStyleQss("hover", it));
                                }
                            }
                            hwi->setStyleSheet(hwi->getJoinStyles());
                            hwi->enterEvent(nullptr);
                        }
                    }
                }
            }
        }
        if (event == nullptr) {
            return;
        }
        auto *enterEvent = dynamic_cast<QEnterEvent *>(event);
        if (this->enterEventCB && enterEvent != nullptr) {
            if (this->geometry().contains(this->mapToParent(enterEvent->pos()))) {
                this->enterEventCB(event);
            }
        }
        QWidget::enterEvent(event);
        emit mouseEnter();
    }

    void HWidget::leaveEvent(QEvent *event) {
        if (this->globalHover) {
            if (this->layout() != nullptr) {
                QLayoutItem *child;
                auto count = this->layout()->count();
                for (int index = 0; index < count; index++) {
                    child = this->layout()->itemAt(index);
                    if (child && child->widget()) {
                        auto *hwi = dynamic_cast<HWidget *>(child->widget());
                        if (hwi != nullptr) {
                            for (const auto &it: this->globalHoverAttributes) {
                                if (this->existStyleQss("!hover", it)) {
                                    hwi->setStyleQssFource("background-color", this->getStyleQss("!hover", it));
                                }
                            }
                            hwi->setStyleSheet(hwi->getJoinStyles());
                            hwi->leaveEvent(nullptr);
                        }
                    }
                }
            }
        }
        if (event == nullptr) {
            return;
        }
        if (this->leaveEventCB) {
            this->leaveEventCB(event);
        }
        QWidget::leaveEvent(event);
        emit mouseLeave();

    }

    void HWidget::mousePressEvent(QMouseEvent *event) {
        QWidget::mousePressEvent(event);
        emit clicked();
    }

    void HWidget::mouseReleaseEvent(QMouseEvent *event) {
        QWidget::mouseReleaseEvent(event);
    }

    void HWidget::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        {
//            https://blog.csdn.net/dee53994040/article/details/102178938
            // 修复使用了 Q_OBJECT 后stylesheet无效的问题
            QStyleOption opt;
            opt.init(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

        }

        QWidget::paintEvent(event);
    }

    void HWidget::setFixed() {
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    bool HWidget::isGlobalHover() const {
        return globalHover;
    }

    void HWidget::setGlobalHover(bool globalHoverPa) {
        this->globalHover = globalHoverPa;
    }

    void HWidget::setStyleSheet(const QString &styleSheet) {
        QWidget::setStyleSheet(styleSheet);
    }

    /**
     * 只移出，不删除
     * @param wid
     */
    void HWidget::removeWidget(QWidget *wid, bool isDelete) {
        if (wid == nullptr) {
            return;
        }
        if (this->layout() != nullptr) {
            QLayoutItem *child;
            auto count = this->layout()->count();
            for (int index = 0; index < count; index++) {
                child = this->layout()->itemAt(index);
                if (child && child->widget() && child->widget() == wid) {
                    this->layout()->takeAt(index);
                    wid->setParent(nullptr);
                    if (isDelete) {
                        delete wid;
                    }
                }
            }
        }
    }

    void HWidget::mouseClick(QPoint globalPos) {
        bool contain = false;
        if (this->geometry().contains(this->mapToParent(this->mapFromGlobal(globalPos)))) {
            contain = true;
            emit clicked();
        }
        if (!contain) {
            return;
        }
        if (this->layout() != nullptr) {
            QLayoutItem *child;
            auto count = this->layout()->count();
            for (int index = 0; index < count; index++) {
                child = this->layout()->itemAt(index);
                if (child && child->widget()) {
                    auto *h = dynamic_cast<HWidget *>(child->widget());
                    if (h != nullptr) {
                        h->mouseClick(globalPos);
                    }
                }
            }
        }
    }

    void HWidget::addWidget(QSpacerItem *item) {
        if (this->vertical) {
            auto *ly = dynamic_cast<QVBoxLayout *>(this->layout());
            ly->addSpacerItem(item);
        } else {
            auto *ly = dynamic_cast<QHBoxLayout *>(this->layout());
            ly->addSpacerItem(item);
        }
    }

    void HWidget::replaceWidget(QWidget *newWidget, QWidget *old, bool isDelete) {
        if (newWidget == nullptr) {
            return;
        }
        if (old != nullptr) {
            if (this->layout() != nullptr) {
                QLayoutItem *child;
                auto count = this->layout()->count();
                for (int index = 0; index < count; index++) {
                    child = this->layout()->itemAt(index);
                    if (child && child->widget() && child->widget() == old) {
                        old->setParent(nullptr);
                        if (isDelete) {
                            delete old;
                        }
                        if (this->vertical) {
                            auto *ly = dynamic_cast<QVBoxLayout *>(this->layout());
                            ly->takeAt(index);
                            ly->insertWidget(index, newWidget);
                        } else {
                            auto *ly = dynamic_cast<QHBoxLayout *>(this->layout());
                            ly->takeAt(index);
                            ly->insertWidget(index, newWidget);
                        }
                        break;
                    }
                }
            }
        }

    }

    std::vector<std::string> &HWidget::getGlobalHoverAttributes() {
        return globalHoverAttributes;
    }


}