#pragma  once

#include "QtSvg/QSvgWidget"
#include "QLabel"
#include "QPixmap"
#include "IconSvg.h"
#include "QIcon"
#include "HWidget.h"

namespace wl {
    class Icon : public QLabel {

    Q_OBJECT
    public:
        Icon(const QString &file, QWidget *parent = nullptr);

        Icon(const QString &label, const QColor &color, QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

        QIcon transToQIcon();

        void enterEvent(QEvent *event) override;

        void leaveEvent(QEvent *event) override;

        void mousePressEvent(QMouseEvent *event) override;

        void mouseReleaseEvent(QMouseEvent *event) override;

    signals:

        void clicked();

        void mouseEnter();

        void mouseLeave();

    private:
        QPixmap originPixmap_;
        QPixmap showPixMap_;
    };


}

