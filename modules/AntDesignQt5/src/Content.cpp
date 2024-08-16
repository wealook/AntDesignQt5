//
///7/9.
//

#include "Content.h"
#include "logger.h"
#include <QScrollBar>
#include "qevent.h"
#include "ThemeConfig.h"

namespace wl {
    Content::Content(QWidget *parent) : QScrollArea(parent) {
        auto themeConfig = ThemeConfig::Instance();
        this->verticalScrollBar()->setStyleSheet(QString::fromStdString(themeConfig.verticalScrollBar));
        this->setStyleSheet("background-color: rgb(255,255,255);");
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    void Content::resizeEvent(QResizeEvent *event) {
//        LOG_INFO(event->size().width() << "," << event->size().height())
        if (this->contentWidget) {
//            if (this->widget()->width() < event->size().width()) {
// TODO 根据情况调整是否设置为固定宽度
            this->widget()->setFixedWidth(event->size().width());
//            }
//            LOG_INFO(this->widget()->size().width() << "," << this->widget()->size().height())
        }

        QScrollArea::resizeEvent(event);
    }

    void Content::setContentWidget(QWidget *pWidget) {
        this->takeWidget();
        this->contentWidget = pWidget;
        this->contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setWidget(contentWidget);
    }

    void Content::paintEvent(QPaintEvent *event) {
        QAbstractScrollArea::paintEvent(event);
        if (this->contentWidget) {
//            if (this->widget()->width() < event->size().width()) {
// TODO 根据情况调整是否设置为固定宽度
            this->widget()->setFixedWidth(this->size().width());
//            }
//            LOG_INFO(this->widget()->size().width() << "," << this->widget()->size().height())
        }
    }
}
