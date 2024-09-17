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
        explicit Icon(QWidget *parent = nullptr);

        explicit Icon(const QString &file, QWidget *parent = nullptr);

        explicit Icon(const QString &label, const QColor &color, QWidget *parent = nullptr);

        void loadBaseSvg(const QString &label, const QColor &color);

        void loadBaseSvg(const QString &label);

        void changeColor(const QColor &color);

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
        QString svgLabel_;
    };


}

