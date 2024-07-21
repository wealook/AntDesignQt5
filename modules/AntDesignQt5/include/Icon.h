#pragma  once

#include "QtSvg/QSvgWidget"
#include "QLabel"
#include "QPixmap"
#include "IconSvg.h"
#include "QIcon"

namespace wl {
    class Icon : public QLabel {
    public:
        Icon(const QString &file, QWidget *parent = nullptr);

        Icon(const QString &label, const QColor &color, QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

        QIcon transToQIcon();

    private:
        QPixmap originPixmap_;
        QPixmap showPixMap_;
    };


}

