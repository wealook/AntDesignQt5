//
///7/15.
//

#include "Icon.h"
#include <QSvgRenderer>
#include <QImage>
#include <QPainter>
#include <QIcon>
#include "qevent.h"
#include "logger.h"

namespace wl {

    Icon::Icon(const QString &file, QWidget *parent) : QLabel(parent) {
        originPixmap_.load(file);
        QPainter qp(&originPixmap_);
        qp.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp.fillRect(originPixmap_.rect(), QColor(Qt::red));
        qp.end();
        if (originPixmap_.rect().width() > 200) {
            originPixmap_ = originPixmap_.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }

//        showPixMap_ = originPixmap_.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        this->setPixmap(showPixMap_);
//        this->setStyleSheet("border:1px solid red");
        this->setStyleSheet("border:none");
        this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        this->setMargin(0);
//        this->setMinimumHeight(30);
    }

    void Icon::resizeEvent(QResizeEvent *event) {
        auto sizeL = std::min(event->size().width(), event->size().height());
        showPixMap_ = originPixmap_.scaled(sizeL, sizeL, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->setPixmap(showPixMap_);
        QWidget::resizeEvent(event);
    }

    Icon::Icon(const QString &label, const QColor &color, QWidget *parent) : QLabel(parent) {
      //  LOG_INFO("t0")
        originPixmap_.load(QString("./icon-svg/" + label + ".svg"));
      //  LOG_INFO("t1")
        QPainter qp(&originPixmap_);
      //  LOG_INFO("t2")

        qp.setCompositionMode(QPainter::CompositionMode_SourceIn);
      //  LOG_INFO("t3")

        qp.fillRect(originPixmap_.rect(), color);
      //  LOG_INFO("t4")

        qp.end();
     //   LOG_INFO("t5")

        if (originPixmap_.rect().width() > 200) {
            originPixmap_ = originPixmap_.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
       // LOG_INFO("t6")
        this->setStyleSheet("border:none");
        this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        this->setMargin(0);
    }

    QIcon Icon::transToQIcon() {
        auto qIcon = QIcon(this->originPixmap_);
        return qIcon;
    }
}