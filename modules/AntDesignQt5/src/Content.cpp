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
        this->setWidgetResizable(true);
    }

    void Content::resizeEvent(QResizeEvent *event) {
        if (this->contentWidget) {
// TODO 根据情况调整是否设置为固定宽度
            if (event->size() != event->oldSize()) {
                this->widget()->setFixedWidth(event->size().width());
            }
        }
    }

    void Content::setContentWidget(QWidget *pWidget) {
        this->takeWidget();
        this->contentWidget = pWidget;
        this->contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setWidget(contentWidget);
        this->widget()->setFixedWidth(this->size().width());
    }

    void Content::paintEvent(QPaintEvent *event) {
        QAbstractScrollArea::paintEvent(event);
    }
}
