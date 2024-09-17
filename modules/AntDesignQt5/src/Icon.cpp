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
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
        this->loadBaseSvg(label, color);
    }

    QIcon Icon::transToQIcon() {
        auto qIcon = QIcon(this->originPixmap_);
        return qIcon;
    }

    void Icon::enterEvent(QEvent *event) {
        QWidget::enterEvent(event);
        emit mouseEnter();
    }

    void Icon::leaveEvent(QEvent *event) {
        QWidget::leaveEvent(event);
        emit mouseLeave();
    }

    void Icon::mousePressEvent(QMouseEvent *event) {
        QLabel::mousePressEvent(event);
        emit clicked();
    }

    void Icon::mouseReleaseEvent(QMouseEvent *event) {
        QLabel::mouseReleaseEvent(event);
    }

    Icon::Icon(QWidget *parent) : QLabel(parent) {

    }

    void Icon::loadBaseSvg(const QString &label, const QColor &color) {
        svgLabel_ = label;
        originPixmap_.load(QString("./icon-svg/" + label + ".svg"));
        QPainter qp(&originPixmap_);
        qp.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp.fillRect(originPixmap_.rect(), color);
        qp.end();
        if (originPixmap_.rect().width() > 200) {
            originPixmap_ = originPixmap_.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        this->setStyleSheet("border:none");
//        this->setStyleSheet("border:1px solid blue");
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setMargin(0);
    }

    void Icon::loadBaseSvg(const QString &label) {
        originPixmap_.load(QString("./icon-svg/" + label + ".svg"));
        if (originPixmap_.rect().width() > 200) {
            originPixmap_ = originPixmap_.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        this->setStyleSheet("border:none");
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setMargin(0);
    }

    void Icon::changeColor(const QColor &color) {
        if (svgLabel_.isEmpty()) {
            return;
        }
        this->loadBaseSvg(svgLabel_, color);
        auto sizeL = this->size();
        showPixMap_ = originPixmap_.scaled(sizeL.width(), sizeL.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->setPixmap(showPixMap_);
    }


}